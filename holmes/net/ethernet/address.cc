// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <sstream>
#include <iomanip>

#include "holmes/parse_error.h"
#include "holmes/net/ethernet/address.h"

namespace holmes::net::ethernet {

address::address(octet::string& raw):
	_raw(read(raw, _length)) {

	if (_raw.length() != _length) {
		throw parse_error("Ethernet address must be 6 octets long");
	}
}

address::operator std::string() const {
	std::ostringstream out;
	out << std::uppercase << *this;
	return out.str();
}

std::ostream& operator<<(std::ostream& out, const address& addr) {
	auto raw = addr.raw();
	size_t len = raw.length();
	for (unsigned int i = 0; i != len; ++i) {
		if (i != 0) {
			out << '-';
		}
		out << raw.substr(i, 1);
	}
	return out;
}

} /* namespace holmes::net::ethernet */
