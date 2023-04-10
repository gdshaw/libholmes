// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/octet/hex/decoder.h"

namespace holmes::octet::hex {

const int8_t decoder::_charset[0x100] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

octet::string decoder::operator()(const std::string& in, bool final) {
	size_t reserve = in.length() / 2;
	if ((_count != 0) && (in.length() % 2 != 0)) {
		reserve += 1;
	}
	std::basic_string<unsigned char> out;
	out.reserve(reserve);
	for (auto c : in) {
		unsigned char uc = c;
		int8_t v = _charset[uc];
		if (v >= 0) {
			// Handle substantive content.
			_buffer <<= 4;
			_buffer |= v;
			_count += 4;
			if (_count == 8) {
				out.push_back(_buffer);
				_buffer = 0;
				_count = 0;
			}
		} else if (v == -2) {
			// Handle content which should be disregarded.
		} else {
			// Handle any other character.
			throw parse_error("invalid character in hex data");
		}
	}

	if (final && (_count != 0)) {
		throw parse_error("odd number of digits in hex data");
	}
	return octet::string(out);
}

} /* namespace holmes::octet::hex */
