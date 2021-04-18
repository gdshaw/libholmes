// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/writer.h"
#include "holmes/bson/int32.h"

namespace holmes::bson {

int32::int32(int32_t value):
	_value(value) {}

int32::int32(octet::string& bd, const value::decode& dec):
	_value(read_int32(bd, -1)) {}

std::unique_ptr<value> int32::clone() const {
	return std::make_unique<int32>(*this);
}

unsigned char int32::type() const {
	return 0x10;
}

size_t int32::length() const {
	return 4;
}

void int32::encode(writer& bw) const {
	write_int32(bw, _value);
}

std::string int32::to_json() const {
	return std::to_string(_value);
}

} /* namespace holmes::bson */
