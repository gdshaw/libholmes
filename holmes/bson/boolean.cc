// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/writer.h"
#include "holmes/bson/boolean.h"

namespace holmes::bson {

boolean::boolean(bool value):
	_value(value) {}

boolean::boolean(octet::string& bd, const value::decode& dec):
	_value(read_uint8(bd)) {

	if ((_value & ~1) != 0) {
		throw std::invalid_argument("invalid encoding for BSON boolean");
	}
}

std::unique_ptr<value> boolean::clone() const {
	return std::make_unique<boolean>(*this);
}

unsigned char boolean::type() const {
	return 0x08;
}

size_t boolean::length() const {
	return 1;
}

void boolean::encode(writer& bw) const {
	write_uint8(bw, _value);
}

std::string boolean::to_json() const {
	return (_value) ? "true" : "false";
}

} /* namespace holmes::bson */
