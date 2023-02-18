// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/net/inet6/address.h"

namespace holmes::net::inet6 {

address* address::_clone() const {
	return new address(*this);
}

void address::_write(std::ostream& out) const {
	auto& _data = data();
	uint16_t words[8];
	unsigned int maxrunpos = 0;
	unsigned int maxrunlen = 0;
	unsigned int currunpos = 0;
	for (unsigned int i = 0; i != 8; ++i) {
		uint16_t word = get_uint16(_data, i * 2);
		words[i] = word;
		if (word != 0) {
			unsigned int currunlen = i - currunpos;
			if (currunlen > maxrunlen) {
				maxrunpos = currunpos;
				maxrunlen = currunlen;
			}
			currunpos = i + 1;
		}
	}
	unsigned int currunlen = 8 - currunpos;
	if (currunlen > maxrunlen) {
		maxrunpos = currunpos;
		maxrunlen = currunlen;
	}
	if (maxrunlen < 2) {
		maxrunlen = 0;
	}

	std::ios_base::fmtflags flags(out.flags());
	out << std::hex;
	for (unsigned int i = 0; i != 8; ++i) {
		if ((i < maxrunpos) || (i >= maxrunpos + maxrunlen)) {
			if (i != 0) {
				out << ":";
			}
			out << words[i];
		} else if (i == maxrunpos) {
			out << ":";
		}
	}
	if (maxrunpos + maxrunlen == 8) {
		out << ":";
	}
	out.flags(flags);
}

address::address(const octet::string& data):
	inet::address(data) {

	if (data.length() != 16) {
		throw parse_error("IPv6 address must be 16 octets long");
	}
}

} /* namespace holmes::net::inet6 */
