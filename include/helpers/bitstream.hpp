//
//  Made by Fran 1024, 2019
//  https://github.com/FranX1024/bitstream/blob/master/bitstream.cpp
//
//  Modified by Aske Wachs
//

#ifndef THESIS_BITSTREAM_HPP
#define THESIS_BITSTREAM_HPP

#include <cstdlib>
#include "helpers/swap_endian.hpp"
#include "helpers/types.hpp"
#include "assert.hpp"

/*

*/

enum class streamtype {
    UNDEFINED,
    READ,
    WRITE,
};

class bitstream {
private:
    byte_t *_data;
    uint64_t _size;
    uint64_t _index = 0;
    streamtype _type = streamtype::UNDEFINED;

    template<streamtype T>
    inline void check_type(){
        if (_type == T)
            return;

        throw std::exception();
    }
public:

    void open_read(const byte_t* bytes, uint64_t size) {
        check_type<streamtype::UNDEFINED>();
        _type = streamtype::READ;
        _data = const_cast<byte_t*>(bytes);
        _size = size * 8;
    }
    void open_write(byte_t* bytes, uint64_t size)    {
        check_type<streamtype::UNDEFINED>();
        _type = streamtype::WRITE;
        _size = size * 8;
        _data = bytes;
        bzero(_data, size);
    }
    bool has_more_bits() const {
        return _index < _size;
    }
    template<typename T>
    void write(T t, uint32_t bits) {
//        D_ASSERT(sizeof(T) * 8 >= bits);
        check_type<streamtype::WRITE>();
        auto t_bytes = reinterpret_cast<byte_t*>(&t);

        for(uint8_t i = 0; i < bits; i++) {
            auto data_bit = (i % 8);
            auto data_index = i / 8;
            auto _bit = (t_bytes[data_index] >> data_bit) & 1ull;

            auto stream_pos = _index + i;
            auto stream_bit = (stream_pos % 8);
            auto stream_index = stream_pos / 8;
            auto stream_byte = _data[stream_index];
            auto mask = _bit << stream_bit;
            auto bit_cleared_result = (stream_byte) & ~mask;
            auto result = bit_cleared_result | mask;
            _data[stream_index] = result;
        }
        _index += bits;
    }
    // reads from bitstream
    template<typename T>
    T read(uint32_t bits) {
        check_type<streamtype::READ>();
        const byte_t* data = _data;
        T dat = 0;
        const auto lim = _index + bits;
        // TODO increment data pointer on every 8th of index?
        for(; _index < lim; _index++) {
            auto data_bit = 7 - (_index % 8);
            auto data_index = _index / 8;
            auto _bit = (data[data_index] >> data_bit) & 1;
            dat = (dat << 1) | (_bit);
        }
        return dat;
    }
};

#endif //THESIS_BITSTREAM_HPP
