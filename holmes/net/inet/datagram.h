// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_DATAGRAM
#define HOLMES_NET_INET_DATAGRAM

#include "holmes/artefact.h"
#include "holmes/net/inet/checksum.h"

namespace holmes::net::inet {

class address;

/** An abstract base class to represent an IP datagram. */
class datagram:
	public artefact {
public:
	/** Get the raw content of this datagram.
	 * @return the raw content
	 */
	virtual const octet::string& data() const = 0;

	/** Get the version number.
	 * This is taken from the (potentially unvalidated) header content,
	 * so does not necessarily correspond to the dynamic type of the
	 * datagram object.
	 * @return the IP version number
	 */
	unsigned int version() const {
		return (get_uint8(data(), 0) >> 4) & 0xf;
	}

	/** Get the source address.
	 * @return the source address
	 */
	virtual const address& src_addr() const = 0;

	/** Get the destination address.
	 * @return the destination address
	 */
	virtual const address& dst_addr() const = 0;

	/** Make checksum for pseudo-header.
	 * @return the checksum object
	 */
	virtual inet::checksum make_pseudo_header_checksum() const = 0;
};

} /* namespace holmes::net::inet4 */

#endif
