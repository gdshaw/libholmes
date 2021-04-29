// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/octet/base64/decoder.h"

namespace holmes::octet::base64 {

const int8_t decoder::_charset[0x100] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

octet::string decoder::operator()(const std::string& in) {
	unsigned int groups = (in.length() + 3) / 4;
	std::basic_string<unsigned char> out;
	bool padding = false;
	out.reserve(groups * 3);
	for (auto c : in) {
		unsigned char uc = c;
		int8_t v = _charset[uc];
		if (v >= 0) {
			// Handle substantive content.
			if (padding) {
				throw parse_error("invalid base64 data following padding");
			}
			_buffer <<= 6;
			_buffer |= v;
			_count += 6;
			if (_count >= 8) {
				_count -= 8;
				unsigned char b = (_buffer >> _count) & 0xff;
				out.push_back(b);
			}
		} else if (v == -2) {
			// Handle padding character (equals sign).
			// This should not occur if there is any undecoded data in the
			// buffer, and if it does occur, then there should be no further
			// substantive content.
			unsigned int mask = (1 << _count) - 1;
			if (_buffer & mask) {
				throw parse_error("invalid use of base64 padding");
			}
			padding = true;
		} else {
			// Handle any other character.
			throw parse_error("invalid character in base64 data");
		}
	}
	return octet::string(out);
}

} /* namespace holmes::octet::base64 */
