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
//        auto iter = in.cbegin();
//        auto const n = *reinterpret_cast<const uint8_t*>(&*iter);
//        iter++;
        bitstream b{};
        auto data = in.data();
        b.openBytes(data, in.size());
        const auto n = b.read<uint8_t>(8);
        const uint64_t reset_marker = -1ull >> (64 - n);
        uint64_t prev_x = b.read<uint64_t>(64);
        out.push_back(*reinterpret_cast<double_t*>(&prev_x));

//        uint64_t prev_x = (*reinterpret_cast<const uint64_t*>(&*iter));
//        iter++;
//        prev_x += (*reinterpret_cast<const uint64_t*>(&*iter)) << 32;
//        iter++;
//        prev_x += (*reinterpret_cast<const uint64_t*>(&*iter)) << 16;
//        iter++;
//        prev_x += *reinterpret_cast<const uint64_t*>(&*iter);
//        iter++;
//        out.push_back(*reinterpret_cast<double*>(prev_x));
//        const auto end = in.cend();
//        while(iter != end) {
//
//        }
    }
} // algorithms