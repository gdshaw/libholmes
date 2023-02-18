// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/net/inet4/address.h"

namespace holmes::net::inet4 {

address::address(const octet::string& data):
	inet::address(data) {

	if (data.length() != 4) {
		throw parse_error("IPv4 address must be 4 octets long");
	}
}

address* address::_clone() const {
	return new address(*this);
}

void address::write(std::ostream& out) const {
	auto data = this->data();
	unsigned int width = out.width();
	out << (data[0] & 0xff) << '.';
	out.width(width);
	out << (data[1] & 0xff) << '.';
	out.width(width);
	out << (data[2] & 0xff) << '.';
	out.width(width);
	out << (data[3] & 0xff);
}

} /* namespace holmes::net::inet4 */
