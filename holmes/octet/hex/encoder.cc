// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/hex/encoder.h"

namespace holmes::octet::hex {

const char* encoder::_charset =
	"0123456789abcdef";

std::string encoder::operator()(const octet::string& in) {
	std::string out;
	out.reserve(in.length() * 2);
	for (auto b : in) {
		out.push_back(_charset[(b >> 4) & 0xf]);
		out.push_back(_charset[(b >> 0) & 0xf]);
	}
	return out;
}

} /* namespace holmes::octet::hex */
