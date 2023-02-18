// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_ADDRESS
#define HOLMES_NET_INET_ADDRESS

#include "holmes/net/address.h"

namespace holmes::net::inet {

/** A class to represent an IP address. */
class address:
	public net::address {
protected:
	address* _clone() const override = 0;
public:
	/** Construct IP address from raw content.
	 * @param data the required raw content
	 */
	explicit address(const octet::string& data):
		net::address(data) {}

	/** Clone this address.
	 * @return the cloned address
	 */
	std::unique_ptr<address> clone() const {
		return std::unique_ptr<address>(_clone());
	}
};

} /* namespace holmes::net::inet */

#endif
