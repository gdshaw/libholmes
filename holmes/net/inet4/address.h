// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET4_ADDRESS
#define HOLMES_NET_INET4_ADDRESS

#include <iostream>

#include "holmes/net/inet/address.h"

namespace holmes::net::inet4 {

/** A class to represent an IPv4 address. */
class address:
	public inet::address {
public:
	/** Construct IPv4 address from raw content.
	 * @param data the raw content
	 */
	explicit address(const octet::string& data);

	void write(std::ostream& out) const override;
};

} /* namespace holmes::net::inet4 */

#endif
