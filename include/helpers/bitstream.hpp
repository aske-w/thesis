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
/*

*/

class bitstream {
private:
    const byte_t *data; // where bitstream is contained
    int size;   // size of the bitstream
    uint64_t index = 0;
public:
    // returns data as a byte array
//    const byte_t *toByteArray() {
//        return data;
//    }
    /**************************/
    bool getbit(byte_t x, uint64_t y) {
        return (x >> (7 - y)) & 1;
    }
//    int chbit(int x, int i, bool v) {
//        if(v) return x | (1 << (7 - i));
//        return x & ~(1 << (7 - i));
//    }
    /**************************/

    // opens an existing byte array as bitstream
    void openBytes(const byte_t *bytes, int _size) {
        data = bytes;
        size = _size;
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
        for(uint64_t i = index; i < index + bits; i++) {
            dat = (dat << 1) | getbit(data[i / 8], i % 8);
        }
        index += bits;
        return swap_endian(dat);
    }
};

#endif //THESIS_BITSTREAM_HPP
