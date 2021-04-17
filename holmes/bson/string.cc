// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <cstdio>
#include <stdexcept>

#include "holmes/parse_error.h"
#include "holmes/unicode/utf8/decoder.h"
#include "holmes/bson/writer.h"
#include "holmes/bson/string.h"

namespace holmes::bson {

string::string(const std::string& value):
	_value(value) {}

std::unique_ptr<value> string::clone() const {
	return std::make_unique<string>(*this);
}

unsigned char string::type() const {
	return 0x02;
}

size_t string::length() const {
	return _value.length() + 5;
}

void string::encode(writer& bw) const {
	write_int32(bw, _value.length() + 1);
	write(bw, _value.data(), _value.length());
	write_uint8(bw, 0);
}

std::string string::to_json() const {
	// Characters are escaped only if they must be.
	// The reserved capacity currently makes no allowance for escaped
	// characters, however scanning would be necessary to obtain an
	// accurate predication in all cases, and for typical workloads
	// there would be a risk of this doing more harm than good.
	std::string result;
	result.reserve(_value.length() + 2);
	result.push_back('"');
	octet::string octets(
		reinterpret_cast<const unsigned char*>(_value.data()),
		_value.length());
	unicode::utf8::decoder decoder(octets);
	while (decoder) {
		uint32_t cp = decoder();
		std::cout << std::hex << cp << std::dec << "\n";

		if (cp < 0x20) {
			switch (cp) {
			case '\b':
				result.push_back('\\');
				result.push_back('b');
				break;
			case '\t':
				result.push_back('\\');
				result.push_back('t');
				break;
			case '\n':
				result.push_back('\\');
				result.push_back('n');
				break;
			case '\f':
				result.push_back('\\');
				result.push_back('f');
				break;
			case '\r':
				result.push_back('\\');
				result.push_back('r');
				break;
			default:
				char buffer[7];
				sprintf(buffer, "\\u%04X", cp);
				result.append(buffer);
				break;
			}
		} else if (cp < 0x80) {
			switch (cp) {
			case '"':
				result.push_back('\\');
				result.push_back('\"');
				break;
			case '\\':
				result.push_back('\\');
				result.push_back('\\');
				break;
			default:
				result.push_back(cp);
				break;
			}
		} else if (cp < 0x10000) {
			char buffer[7];
			sprintf(buffer, "\\u%04X", cp);
			result.append(buffer);
			break;
		} else if (cp < 0x110000) {
			uint16_t hscp = 0xd800 + ((cp - 0x10000) >> 10);
			uint16_t lscp = 0xdc00 + ((cp - 0x10000) & 0x3ff);
			char buffer[14];
			sprintf(buffer, "\\u%04X\\u%04X", hscp, lscp);
			result.append(buffer);
			break;
		} else {
			throw parse_error("code point out of range");
		}
	}
	result.push_back('"');
	return result;
}

std::unique_ptr<string> string::decode(octet::string& bd) {
	int32_t length = read_int32(bd, -1);
	if (length < 1) {
		throw std::invalid_argument("invalid length in BSON string");
	}
	bd.at(length - 1);
	octet::string content = read(bd, length);
	if (content[length - 1] != 0) {
		throw std::invalid_argument("missing terminator in BSON string");
	}
	std::string value(reinterpret_cast<const char*>(content.data()),
		length - 1);
	return std::make_unique<string>(value);
}

} /* namespace holmes::bson */
