//
// Created by Aske Wachs on 03/02/2024.
//

#include "algorithms/spatialparquet_java_port.hpp"
#include "helpers/bitstream.hpp"
#include <iostream>
#include <bit>
#include <cmath>
using std::vector;
using std::bit_cast;

namespace algorithms {
    std::unique_ptr<byte_t*> spatialparquet_java_port::encode(const vector<double_t>& in) {
        std::array<uint32_t, 64> bitCounter {};
        bitCounter.fill(0);
        int64_t prev_double_long = 0;
        uint64_t totalValues = 0;
        for (auto&& d : in) {
            auto l  = *reinterpret_cast<const int64_t *>(&d);
            auto diff = l - prev_double_long;
            diff = (diff >> 63) ^ (diff << 1);
            uint8_t leadingZeros = __builtin_clzll(diff);
            if((-1l >> leadingZeros) == diff || diff == 0){
                leadingZeros = std::max(leadingZeros - 1, 0);
            }
            bitCounter[leadingZeros]++;
//            std::cout << d << " became " << std::hex << diff << std::endl;
            prev_double_long = l;
            totalValues++;
        }

        uint32_t currentCount = 0;
        uint64_t finalSize = sizeof(double_t) * in.size() * 8 + 8;
        int32_t redundantBits = 0;
        const uint8_t bitsInType = sizeof(double_t) * 8;
        for (uint8_t i = 0; i < bitsInType; i++) {
            const auto bitCount = bitCounter[i];
            if (bitCount == 0)
                continue;
            currentCount += bitCount;
            uint64_t newSize = totalValues * (64 - i) + currentCount * 64 + 8;
            if (newSize < finalSize) {
                finalSize = newSize;
                redundantBits = i;
            }
        }

        uint8_t bits = sizeof(double_t) * 8 - (redundantBits);
        uint64_t max = -1ull >> redundantBits;
        int64_t leadingOnes = -1l << bits;

        auto out_size = in.size() * sizeof(double_t);
        auto out = std::make_unique<byte_t*>(new byte_t[out_size]);
        bitstream outstream;
        outstream.open_write(*out, out_size);
        outstream.write(bits, 8);
        bitstream instream;
        instream.open_read(reinterpret_cast<const byte_t *>(in.data()), in.size());

        auto item = in.cbegin();
        auto end = in.cend();
        auto curr = bit_cast<int64_t>(*item);
        auto prev = 0ll;
        while(item != end) {
            int64_t delta = curr - prev;
            int64_t zigzag = (delta >> 63) ^ (delta << 1);
            int64_t common = zigzag & leadingOnes;
            if (common != 0 || zigzag == max) {
                outstream.write(max, bits);
                outstream.write(zigzag, 64);
            } else {
                outstream.write(zigzag, bits);
            }
            prev = curr;
            item++;
            curr = bit_cast<int64_t>(*item);
        }
        return out;
    }
    void spatialparquet_java_port::decode(const vector<byte_t>& in, vector<double_t>& out) {
        bitstream b{};
        auto data = in.data();
        b.open_read(data, in.size());

        const auto n = b.read<uint8_t>(8);
        const uint64_t reset_marker = -1ull >> (64 - n);
        int64_t prev = 0;

        while (b.has_more_bits()) {
            int64_t tmp;
            if (n == 64) {
                tmp = b.read<int64_t>(64);
            } else {
                // TODO maybe this can be signed
                tmp = b.read<uint64_t>(n);
                std::cout << std::hex << tmp << std::endl;
                if (tmp == reset_marker) {
                    tmp = b.read<int64_t>(64);
                    std::cout << "\t" << std::hex << tmp << std::endl;
                }
            }
            tmp = ((tmp >> 1) ^ -(tmp & 1)) + prev;
            prev = tmp;
            out.push_back(*reinterpret_cast<double_t*>(&tmp));
        }
    }
} // algorithms