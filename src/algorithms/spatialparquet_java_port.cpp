//
// Created by Aske Wachs on 03/02/2024.
//

#include "algorithms/spatialparquet_java_port.hpp"
#include "helpers/bitstream.hpp"
#include <iostream>
#include <bit>
#include <cmath>
using std::vector;

namespace algorithms {
    void spatialparquet_java_port::encode(const vector<double_t>& in, vector<byte_t>& out) {
        std::array<uint32_t, 64> bitCounter {};
//        std::array<uint32_t, 64> _bitCounter {
//            0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 6, 4, 2, 3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//        };
        bitCounter.fill(0);
        int64_t prev = 0;
        uint64_t totalValues = 0;
        for (auto&& d : in) {
            auto l  = *reinterpret_cast<const int64_t *>(&d);
            auto diff = l - prev;
            diff = (diff >> 63) ^ (diff << 1);
            uint8_t leadingZeros = __builtin_clzll(diff);
            if((-1l >> leadingZeros) == diff || diff == 0){
                leadingZeros = std::max(leadingZeros - 1, 0);
            }
            bitCounter[leadingZeros]++;
            prev = l;
            totalValues++;
        }
////        auto double_bytes = vector<byte_t>(in.begin(), in.end());
////        auto data = double_bytes.data();
//        b.openBytes(reinterpret_cast<const byte_t*>(in.data()), in.size());

        throw std::exception{};
    }
    void spatialparquet_java_port::decode(const vector<byte_t>& in, vector<double_t>& out) {
        bitstream b{};
        auto data = in.data();
        b.openBytes(data, in.size());

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