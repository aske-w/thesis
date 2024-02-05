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
    const byte_t *data; // where bitstream is contained
    uint64_t size;   // size of the bitstream
    uint64_t index = 0;
public:
    // returns data as a byte array
//    const byte_t *toByteArray() {
//        return data;
//    }
    /**************************/
    byte_t getbit(byte_t x, uint64_t y) {
        return (x >> y) & 1;
    }
//    int chbit(int x, int i, bool v) {
//        if(v) return x | (1 << (7 - i));
//        return x & ~(1 << (7 - i));
//    }
    /**************************/

    // opens an existing byte array as bitstream
    void openBytes(const byte_t *bytes, uint64_t _size) {
        data = bytes;
        size = _size * 8;
    }
    bool has_more_bits() const {
        return index < size;
    }
    // creates a new bit stream
//    void open(int _size) {
//        data = (char*)malloc(_size);
//        size = _size;
//    }
    // closes bit stream (frees memory)
//    void close() {
//        free(data);
//    }
    // writes to bitstream
//    void write(int index, int bits, int dat) {
//        index += bits;
//        while(dat) {
//            data[index / 8] = chbit(data[index / 8], index % 8, dat & 1);
//            dat /= 2;
//            index--;
//        }
//    }
    // reads from bitstream
    template<typename T>
    T read(uint32_t bits) {
        T dat = 0;
        // 0000000000000011001101010000000100000101110010111111101011101010
        for(uint64_t i = 0; i < bits; i++) {
            auto bit = getbit(data[index / 8 + i / 8], i % 8);
            auto shift = i;
            auto shifted_bit = (bit | 0ull) << shift;
            dat = dat | (shifted_bit);
        }
//        auto padding = sizeof(T) * 8 - bits;
//        dat = swap_endian(dat);
//        dat >>= padding;
        index += sizeof(T) * 8;
        return dat;
    }
};

#endif //THESIS_BITSTREAM_HPP
