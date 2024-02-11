//
// Created by Aske Wachs on 11/02/2024.
//

#include "helpers/bitstream.hpp"
#include <cstring>

namespace thesis {
namespace helpers {

using thesis::helpers::byte_t;
using thesis::helpers::double_t;

void Bitstream::OpenRead(const byte_t* bytes, uint64_t bytes_size) {
	CheckType<Streamtype::UNDEFINED>();
	type = Streamtype::READ;
	data = const_cast<byte_t*>(bytes);
	size = bytes_size * 8;
}

void Bitstream::OpenWrite(byte_t* bytes, uint64_t bytes_size)    {
	CheckType<Streamtype::UNDEFINED>();
	type = Streamtype::WRITE;
	size = bytes_size * 8;
	data = bytes;
	memset(data, 0, size);
}

bool Bitstream::HasMoreBits() const {
	return index < size;
}

}
}
