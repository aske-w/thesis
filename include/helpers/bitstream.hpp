//
//  Made by Fran 1024, 2019
//  https://github.com/FranX1024/bitstream/blob/master/bitstream.cpp
//
//  Modified by Aske Wachs
//

#ifndef HELPERS_BITSTREAM_HPP
#define HELPERS_BITSTREAM_HPP

#include <cstdlib>
#include "helpers/swap_endian.hpp"
#include "helpers/types.hpp"
#include "assert.hpp"

namespace thesis {
namespace helpers {

using thesis::helpers::byte_t;
using thesis::helpers::double_t;

enum class Streamtype {
    UNDEFINED,
    READ,
    WRITE,
};

class Bitstream {
private:
    byte_t * data;
    uint64_t size;
    uint64_t index = 0;
    Streamtype type = Streamtype::UNDEFINED;

    template<Streamtype T>
    inline void CheckType(){
        if (type == T) {
            return;
		}

        throw std::exception();
    }
public:

    void OpenRead(const byte_t* bytes, uint64_t bytes_size);
    void OpenWrite(byte_t* bytes, uint64_t bytes_size);
    bool HasMoreBits() const;
    template<typename T>
    void Write(T t, uint32_t bits) {
		//        D_ASSERT(sizeof(T) * 8 >= bits);

		auto p = SwapEndian(t);
		auto offset = sizeof(T) * 8 - bits;
		CheckType<Streamtype::WRITE>();
		auto t_bytes = reinterpret_cast<byte_t*>(&p);

		for(uint32_t i = 0; i < bits; i++) {
			auto data_bit = 7 - ((i + offset) % 8);
			auto data_index = (i + offset) / 8;
			auto bit = (t_bytes[data_index] >> data_bit) & 1ull;

			auto stream_pos = index + i;
			auto stream_bit = 7- (stream_pos % 8);
			auto stream_index = stream_pos / 8;
			auto stream_byte = data[stream_index];
			auto mask = bit << stream_bit;
			auto bit_cleared_result = (stream_byte) & ~mask;
			auto result = bit_cleared_result | mask;
			data[stream_index] = result;
		}
		index += bits;
	}
    // reads from bitstream
    template<typename T>
    T Read(uint32_t bits) {
		CheckType<Streamtype::READ>();
		T dat = 0;
		const auto lim = index + bits;
		// TODO increment data pointer on every 8th of index?
		for(; index < lim; index++) {
			auto data_bit = 7 - (index % 8);
			auto data_index = index / 8;
			auto bit = (data[data_index] >> data_bit) & 1;
			dat = (dat << 1) | (bit);
		}
		return dat;
	}
};

}
}

#endif //HELPERS_BITSTREAM_HPP