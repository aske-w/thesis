//
// Created by Aske Wachs on 04/02/2024.
//

#ifndef HELPERS_SWAP_ENDIAN_HPP
#define HELPERS_SWAP_ENDIAN_HPP

#include <climits>
#include <cstdint>
namespace thesis {
namespace helpers {

//! Compiles to REV instruction on ARM clang with -03
//! and BSWAP or ROL on x86 gcc
//! from https://stackoverflow.com/a/4956493
template <typename T>
T SwapEndian(T u) {
	static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

	union {
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (uint32_t k = 0; k < sizeof(T); k++) {
		dest.u8[k] = source.u8[sizeof(T) - k - 1];
	}

	return dest.u;
}

}
}
#endif //HELPERS_SWAP_ENDIAN_HPP
