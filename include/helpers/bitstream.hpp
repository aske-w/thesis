//
//  Made by Fran 1024, 2019
//  https://github.com/FranX1024/bitstream/blob/master/bitstream.cpp
//
//  Modified by Aske Wachs
//

#ifndef THESIS_BITSTREAM_HPP
#define THESIS_BITSTREAM_HPP

#include <stdlib.h>
#include "helpers/swap_endian.hpp"
#include "helpers/types.hpp"
/*

*/

class bitstream {
private:
    const byte_t *data;
    uint64_t size;
    uint64_t index = 0;
public:

    void openBytes(const byte_t *bytes, uint64_t _size) {
        data = bytes;
        size = _size * 8;
    }
    bool has_more_bits() const {
        return index < size;
    }
    // reads from bitstream
    template<typename T>
    T read(uint32_t bits) {
        T dat = 0;
        const auto lim = index + bits;
        // TODO increment data pointer on every 8th of index?
        for(; index < lim; index++) {
            auto data_bit = 7 - (index % 8);
            auto data_index = index / 8;
            auto _bit = (data[data_index] >> data_bit) & 1;
            dat = (dat << 1) | (_bit);
        }
        return dat;
    }
};

#endif //THESIS_BITSTREAM_HPP
