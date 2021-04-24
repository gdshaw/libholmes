// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/writer.h"
#include "holmes/bson/array.h"

namespace holmes::bson {

array::array(octet::string& bd, const decode& dec) {
	int32_t length = read_int32(bd, -1);
	if (length < 5) {
		throw std::invalid_argument("invalid length in BSON array");
	}
	octet::string content = read(bd, length - 4);

	size_t index = 0;
	unsigned char type = read_uint8(content);
	while (type != 0) {
		std::string k = read_cstring(content);
		if (k != std::to_string(index)) {
			throw std::invalid_argument("unexpected key in BSON array");
		}
		auto v = any(type, content);
		append(v);
		index += 1;
		type = read_uint8(content);
	}
}

std::unique_ptr<value> array::clone() const {
	return std::make_unique<array>(*this);
}

unsigned char array::type() const {
	return 0x04;
}

size_t array::length() const {
	size_t len = 5;
	size_t index = 0;
	size_t nlen = 2;
	size_t limit = 10;
	for (auto& member : _members) {
		len += 1 + nlen + member.length();
		index += 1;
		if (index == limit) {
			nlen += 1;
			limit *= 10;
		}
	}
	return len;
}

void array::encode(writer& bw) const {
	write_int32(bw, length());
	size_t index = 0;
	for (auto& member : _members) {
		write_uint8(bw, member.type());
		write_cstring(bw, std::to_string(index).c_str());
		member.encode(bw);
		index += 1;
	}
	write_uint8(bw, 0);
}

std::string array::to_json() const {
	std::string result;
	result.push_back('[');
	bool first = true;
	for (auto& member : _members) {
		if (first) {
			first = false;
		} else {
			result.push_back(',');
		}
		result.append(member.to_json());
	}
	result.push_back(']');
	return result;
}

bson::any& array::at(size_t index) {
	return _members.at(index);
}

const bson::any& array::at(size_t index) const {
	return _members.at(index);
}

void array::append(const value& value) {
	_members.push_back(bson::any(value));
}

} /* namespace holmes::bson */
