// This file is part of libholmes.
// Copyright 2020 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/base64/encoder.h"
#include "holmes/bson/writer.h"
#include "holmes/bson/binary.h"

namespace holmes::bson {

binary::binary(const octet::string& value):
	_value(value) {}

std::unique_ptr<value> binary::clone() const {
	return std::make_unique<binary>(*this);
}

unsigned char binary::type() const {
	return 0x05;
}

size_t binary::length() const {
	return _value.length() + 5;
}

void binary::encode(writer& bw) const {
	write_int32(bw, _value.length());
	write_uint8(bw, 0);
	write(bw, _value.data(), _value.length());
}

std::string binary::to_json() const {
	std::string result;
	result.append("{\"$binary\":{\"base64\":\"");
	result.append(octet::base64::encoder()(_value, true));
	result.append("\",\"subtype\":\"0\"}}");
	return result;
}

std::unique_ptr<binary> binary::decode(octet::string& bd) {
	int32_t length = read_int32(bd, -1);
	if (length < 0) {
		throw std::invalid_argument("invalid length in BSON binary data");
	}
	unsigned char subtype = read_uint8(bd);
	if (subtype != 0) {
		throw std::invalid_argument(
			"unsupported subtype in BSON binary data");
	}
	octet::string value = read(bd, length);
	return std::make_unique<binary>(value);
}

} /* namespace holmes::bson */
