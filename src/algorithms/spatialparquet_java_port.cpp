//
// Created by Aske Wachs on 03/02/2024.
//

#include "algorithms/spatialparquet_java_port.hpp"
#include "helpers/bitstream.hpp"

using std::vector;

namespace algorithms {
    void spatialparquet_java_port::encode(const vector<double_t>& in, vector<byte_t>& out) {
        throw std::exception{};
    }
    void spatialparquet_java_port::decode(const vector<byte_t>& in, vector<double_t>& out) {
        bitstream b{};
        auto data = in.data();
        b.openBytes(data, in.size());
        const auto n = b.read<uint8_t>(8);
        const uint64_t reset_marker = -1ull >> (64 - n);
        uint64_t prev = 0;
        auto curr = b.read<uint64_t>(64);
        auto tmp = ((curr >> 1) ^ -(curr & 1)) + prev;
        double_t coord = *reinterpret_cast<double_t*>(&tmp);
        out.push_back(coord);
        prev = tmp;
        while (b.has_more_bits()) {
            auto zigzag = b.read<uint64_t>(n);
            if (zigzag != reset_marker) {
                auto delta = ((zigzag >> 1) ^ -(zigzag & 1));
                curr = prev + delta;
            } else {
                curr = b.read<uint64_t>(64);
            }
            out.push_back(*reinterpret_cast<double_t*>(&curr));
            prev = curr;
        }

//        uint64_t curr = (*reinterpret_cast<const uint64_t*>(&*iter));
//        iter++;
//        curr += (*reinterpret_cast<const uint64_t*>(&*iter)) << 32;
//        iter++;
//        curr += (*reinterpret_cast<const uint64_t*>(&*iter)) << 16;
//        iter++;
//        curr += *reinterpret_cast<const uint64_t*>(&*iter);
//        iter++;
//        out.push_back(*reinterpret_cast<double*>(curr));
//        const auto end = in.cend();
//        while(iter != end) {
//
//        }
    }
} // algorithms