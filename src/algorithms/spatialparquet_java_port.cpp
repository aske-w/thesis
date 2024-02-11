//
// Created by Aske Wachs on 03/02/2024.
//

#include "algorithms/spatialparquet_java_port.hpp"
#include "helpers/bitstream.hpp"
#include <iostream>
#include <bit>

using std::vector;
using std::bit_cast;
using thesis::helpers::double_t;
using thesis::helpers::byte_t;
using thesis::helpers::Bitstream;

namespace thesis {
namespace algorithms {

std::unique_ptr<byte_t*> SpatialParquetJavaPort::Encode(const vector<double_t>& in) {
	std::array<uint32_t, 64> bit_counter {};
	bit_counter.fill(0);
	int64_t prev_double_long = 0;
	uint64_t total_values = 0;
	for (auto&& d : in) {
		auto l = *reinterpret_cast<const int64_t*>(&d);
		auto diff = l - prev_double_long;
		diff = (diff >> 63) ^ (diff << 1);
		uint8_t leading_zeros = __builtin_clzll(diff);
		if ((-1l >> leading_zeros) == diff || diff == 0) {
			leading_zeros = std::max(leading_zeros - 1, 0);
		}
		bit_counter[leading_zeros]++;
		//            std::cout << d << " became " << std::hex << diff << std::endl;
		prev_double_long = l;
		total_values++;
	}

	uint64_t current_count = 0;
	uint64_t final_size = sizeof(double_t) * in.size() * 8 + 8;
	int32_t redundant_bits = 0;
	const uint8_t bitsInType = sizeof(double_t) * 8;
	for (uint8_t i = 0; i < bitsInType; i++) {
		const auto bit_count = bit_counter[i];
		if (bit_count == 0) {
			continue;
		}
		current_count += bit_count;
		uint64_t new_size = total_values * (64 - i) + current_count * 64 + 8;
		if (new_size < final_size) {
			final_size = new_size;
			redundant_bits = i;
		}
	}

	uint8_t bits = sizeof(double_t) * 8 - (redundant_bits);
	uint64_t max = -1ull >> redundant_bits;
	int64_t leading_ones = -1l << bits;

	auto out_size = in.size() * sizeof(double_t);
	auto out = std::make_unique<byte_t*>(new byte_t[out_size]);
	Bitstream outstream;
	outstream.OpenWrite(*out, out_size);
	outstream.Write(bits, 8);
	Bitstream instream;
	instream.OpenRead(reinterpret_cast<const byte_t*>(in.data()), in.size());

	auto item = in.cbegin();
	auto end = in.cend();
	auto curr = bit_cast<int64_t>(*item);
	auto prev = 0ll;
	while (item != end) {
		int64_t delta = curr - prev;
		int64_t zigzag = (delta >> 63) ^ (delta << 1);
		int64_t common = zigzag & leading_ones;
		if (bits < 64 && (common != 0 || zigzag == max)) {
			outstream.Write(max, bits);
			outstream.Write(zigzag, 64);
		} else {
			outstream.Write(zigzag, bits);
		}
		prev = curr;
		item++;
		curr = bit_cast<int64_t>(*item);
	}
	return out;
}
std::unique_ptr<vector<double_t>> SpatialParquetJavaPort::Decode(const vector<byte_t>& in) {
	auto out = std::make_unique<vector<double_t>>();
	Bitstream b {};
	auto data = in.data();
	b.OpenRead(data, in.size());

	const auto n = b.Read<uint8_t>(8);
	const uint64_t reset_marker = -1ull >> (64 - n);
	int64_t prev = 0;

	while (b.HasMoreBits()) {
		int64_t tmp;
		if (n == 64) {
			tmp = b.Read<int64_t>(64);
		} else {
			// TODO maybe this can be signed
			tmp = b.Read<uint64_t>(n);
			std::cout << std::hex << tmp << '\n';
			if (tmp == reset_marker) {
				tmp = b.Read<int64_t>(64);
				std::cout << "\t" << std::hex << tmp << '\n';
			}
		}
		tmp = ((tmp >> 1) ^ -(tmp & 1)) + prev;
		prev = tmp;
		out->push_back(*reinterpret_cast<double_t*>(&tmp));
	}
	return out;
}

} // algorithms
} // thesis