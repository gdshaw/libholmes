// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>
#include <utility>
#include <algorithm>

#include "holmes/bson/writer.h"
#include "holmes/bson/string.h"
#include "holmes/bson/document.h"

namespace holmes::bson {

document::document(octet::string& bd, const decode& dec) {
	int32_t length = read_int32(bd, -1);
	if (length < 5) {
		throw std::invalid_argument("invalid length in BSON document");
	}
	octet::string content = read(bd, length - 4);

	unsigned char type = read_uint8(content);
	while (type != 0) {
		std::string k = read_cstring(content);
		auto v = any(type, content);
		append(k, v);
		type = read_uint8(content);
	}
}

std::unique_ptr<value> document::clone() const {
	return std::make_unique<document>(*this);
}

unsigned char document::type() const {
	return 0x03;
}

size_t document::length() const {
	size_t len = 5;
	for (auto& member : _members) {
		len += 1 + member.first.length() + 1 + member.second.length();
	}
	return len;
}

void document::encode(writer& bw) const {
	write_int32(bw, length());
	for (auto& member : _members) {
		write_uint8(bw, member.second.type());
		write_cstring(bw, member.first.c_str());
		member.second.encode(bw);
	}
	write_uint8(bw, 0);
}

std::string document::to_json() const {
	std::string result;
	result.push_back('{');
	bool first = true;
	for (auto& member : _members) {
		if (first) {
			first = false;
		} else {
			result.push_back(',');
		}
		result.append(bson::string(member.first).to_json());
		result.push_back(':');
		result.append(member.second.to_json());
	}
	result.push_back('}');
	return result;
}

document::mapped_type& document::at(const std::string& name) {
	value_type* found = 0;
	for (auto& member : _members) {
		if (member.first == name) {
			if (found) {
				throw std::out_of_range("out of range");
			} else {
				found = &member;
			}
		}
	}
	if (!found) {
		throw std::out_of_range("out of range");
	}
	return found->second;
}

const document::mapped_type& document::at(const std::string& name) const {
	const value_type* found = 0;
	for (const auto& member : _members) {
		if (member.first == name) {
			if (found) {
				throw std::out_of_range("out of range");
			} else {
				found = &member;
			}
		}
	}
	if (!found) {
		throw std::out_of_range("out of range");
	}
	return found->second;
}

void document::append(const std::string& name, const value& value) {
	_members.push_back(std::make_pair(name, bson::any(value)));
}

} /* namespace holmes::bson */
