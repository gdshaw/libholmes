// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/unicode/utf8/decoder.h"

namespace holmes::unicode::utf8 {

decoder::decoder(const octet::string& data):
	_data(data) {}

uint32_t decoder::operator()() {
	if (_data.empty()) {
		throw parse_error("unexpected end of UTF-8");
	}
	uint32_t value = read_uint8(_data);
	uint32_t limit = 0;
	unsigned int extra = 0;
	if ((value & 0x80) == 0x00) {
		// no action
	} else if ((value & 0xc0) == 0x80) {
		throw parse_error("invalid UTF-8");
	} else if ((value & 0xe0) == 0xc0) {
		value &= 0x1f;
		limit = 0x80;
		extra = 1;
	} else if ((value & 0xf0) == 0xe0) {
		value &= 0x0f;
		limit = 0x800;
		extra = 2;
	} else if ((value & 0xf8) == 0xf0) {
		value &= 0x07;
		limit = 0x10000;
		extra = 3;
	} else {
		throw parse_error("invalid UTF-8");
	}
	for (unsigned int i = 0; i != extra; ++i) {
		uint32_t evalue = read_uint8(_data);
		if ((evalue & 0xc0) != 0x80) {
			throw parse_error("invalid UTF-8");
		}
		value <<= 6;
		value |= evalue & 0x3f;
	}
	if (value < limit) {
		throw parse_error("non-canonical UTF-8");
	}
	if ((value >= 0xd800) && (value < 0xe000)) {
		throw parse_error("surrogate in UTF-8");
	}
	return value;
}

} /* namespace holmes::bson */
