#include <iostream>
#include "helpers/types.hpp"
#include "helpers/bitstream.hpp"
#include "algorithms/spatialparquet_java_port.hpp"


int main() {
    bitstream b;
//    uint64_t _in[] = {
//    9199977945051383458,
//    590594705679797,
//    902703438625514,
//
//    };
//    byte_t* __in = reinterpret_cast<byte_t*>(_in);

    std::vector<byte_t> in {0x34,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xfc,0x52,0xe0,0x6b,0x4c,0xbf,0x5,0xe1,0x78,0x8b,0xbd,0xbf,0x90,0xb5,0x30,0x20,0x2f,0x12,0xfe,0xa2,0x80,0xe1,0x91,0xfb,0xfb,0xcf,0x8a,0x1,0x2e,0x31,0xd4,0xf4,0x2b,0x82,0x7d,0xec,0x4c,0xbb,0x6b,0xb3,0xb5,0x2d,0x93,0x25,0x24,0xff,0xf1,0x72,0x26,0x5a,0x56,0x2f,0xbd,0x4b,0x5d,0x6d,0x90,0x3e,0xee,0x56,0x63,0x9b,0x19,0x0,0xb3,0xd5,0x0,0x73,0xa6,0x3a,0x95,0x86,0xf2,0x7c,0x2,0x31,0x89,0xd1,0xec,0x8f,0xe7,0x7f,0x14,0x27,0xe2,0xa0,0x74,0x32,0x5f,0x77,0xe3,0x5a,0x5,0x89,0xbe,0x56,0x2,0x9,0x20,0x4b,0x8a,0x48,0x5f,0xd6,0xe8,0x3e,0xe4,0x4b,0xb2,0x57,0x13,0xa0,0xac,0xc3,0xca,0x20,0x1e,0x57,0x2c,0xfb,0x73,0x5a,0xb,0x49,0x11,0x3c,0xa9,0x28,0xa1,0xbb,0xc,0x3a,0xaf,0x54,0xec,0x8c,0x7d,0x21,0x6b,0x23,0x77,0xa9,0xaf,0xf3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 };
//    std::vector<byte_t> in { 53 };
//    uint64_t sum = 0;
//    for(int i = 0; i < sizeof(uint64_t) * 3; i++){
//        auto b = __in[i];
//        in.push_back(b);
//    }
    std::vector<double_t> out;
    algorithms::spatialparquet_java_port::decode(in, out);
    return 0;
}
