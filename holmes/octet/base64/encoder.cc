// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/base64/encoder.h"

namespace holmes::octet::base64 {

const char* encoder::_charset =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string encoder::operator()(const octet::string& in, bool final) {
	unsigned int groups = (in.length() + 2) / 3;
	std::string out;
	out.reserve(groups * 4);
	for (auto b : in) {
		_buffer <<= 8;
		_buffer |= b;
		_count += 8;
		while (_count >= 6) {
			_count -= 6;
			unsigned int i = (_buffer >> _count) & 0x3f;
			out.push_back(_charset[i]);
		}
	}
	if (final) {
		if (_count > 0) {
			_buffer <<= 8;
			_count += 2;
			unsigned int i = (_buffer >> _count) & 0x3f;
			out.push_back(_charset[i]);
		}
		while (out.length() < groups * 4) {
			out.push_back('=');
		}
	}
	return out;
}

} /* namespace holmes::octet::base64 */
