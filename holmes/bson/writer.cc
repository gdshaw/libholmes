// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/writer.h"

namespace holmes::bson {

unsigned char* writer::write(size_t count) {
	if (_remaining < count) {
		throw std::out_of_range("BSON buffer full");
	}
	auto buffer = _ptr;
	_ptr += count;
	_remaining -= count;
	return buffer;
}

void write_uint8(writer& bw, uint8_t value) {
	bw.write(1)[0] = value;
}

void write_int32(writer& bw, int32_t value) {
	auto buffer = bw.write(4);
	buffer[0] = value >> 0;
	buffer[1] = value >> 8;
	buffer[2] = value >> 16;
	buffer[3] = value >> 24;
}

void write_int64(writer& bw, int64_t value) {
	auto buffer = bw.write(8);
	buffer[0] = value >> 0;
	buffer[1] = value >> 8;
	buffer[2] = value >> 16;
	buffer[3] = value >> 24;
	buffer[4] = value >> 32;
	buffer[5] = value >> 40;
	buffer[6] = value >> 48;
	buffer[7] = value >> 56;
}

} /* namespace holmes::bson */
