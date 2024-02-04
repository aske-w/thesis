#include <iostream>
#include "helpers/types.hpp"
#include "helpers/bitstream.hpp"
#include "algorithms/spatialparquet_java_port.hpp"


int main() {
    bitstream b;
    uint64_t _in[] = {
    9199977945051383458,
    0x7FACE3328C3746A2,
    0x7face3328c3746a2,
    590594705679797,

    };
    byte_t* __in = reinterpret_cast<byte_t*>(_in);
    std::vector<byte_t> in { 53 };
    uint64_t sum = 0;
    for(int i = 0; i < sizeof(uint64_t) * 2; i++){
        auto b = __in[i];
        in.push_back(b);
    }
    std::vector<double_t> out;
    algorithms::spatialparquet_java_port::decode(in, out);
    return 0;
}
