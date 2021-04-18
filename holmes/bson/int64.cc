// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/writer.h"
#include "holmes/bson/int64.h"

namespace holmes::bson {

int64::int64(int64_t value):
	_value(value) {}

int64::int64(octet::string& bd, const value::decode& dec):
	_value(read_int64(bd, -1)) {}

std::unique_ptr<value> int64::clone() const {
	return std::make_unique<int64>(*this);
}

unsigned char int64::type() const {
	return 0x12;
}

size_t int64::length() const {
	return 8;
}

void int64::encode(writer& bw) const {
	write_int64(bw, _value);
}

std::string int64::to_json() const {
	return std::to_string(_value);
}

} /* namespace holmes::bson */
