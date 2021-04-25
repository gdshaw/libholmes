// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ETHERNET_ADDRESS
#define HOLMES_NET_ETHERNET_ADDRESS

#include <string>
#include <iostream>

#include "holmes/octet/string.h"

namespace holmes::net::ethernet {

/** A class to represent an Ethernet address. */
class address {
private:
	/** The length of an Ethernet address, in octets. */
	static const size_t _length = 6;

	/** The raw content of this address. */
	octet::string _raw;
public:
	/** Construct Ethernet address from raw content.
	 * The content is removed from the start of the supplied octet string.
	 * It is an error if less than 6 octets are available.
	 * @param raw a source of raw content
	 */
	explicit address(octet::string& raw);

	/** Get the raw content of this address.
	 * @return the raw content
	 */
	const octet::string& raw() const {
		return _raw;
	}

	/** Convert this Ethernet address to a string, in IEEE format.
	 * Each octet is converted to a pair of hex digits, using upper case
	 * where applicable. The resulting values are then concatenated in
	 * transmission order, separated by hyphens.
	 * @return the address as a string
	 */
	virtual operator std::string() const;
};

/** Write an Ethernet address to an output stream in IEEE format.
 * The format is the same as for operator ethernet::address::std::string(),
 * except that where there is a choice between upper and lower case this is
 * determined by the stream state.
 * @param out the output stream
 * @param addr the Ethernet address
 * @return the output stream
 */
std::ostream& operator<<(std::ostream& out, const address& addr);

} /* namespace holmes::net::ethernet */

#endif
