// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
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
protected:
        address* _clone() const override;
public:
	/** Construct IPv4 address from raw content.
	 * @param data the required raw content
	 */
	explicit address(const octet::string& data);

	void write(std::ostream& out) const override;

	/** Clone this address.
	 * @return the cloned address
	 */
	std::unique_ptr<address> clone() const {
		return std::unique_ptr<address>(_clone());
	}
};

} /* namespace holmes::net::inet4 */

#endif
