// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_WRAPPER
#define HOLMES_NET_INET_WRAPPER

namespace holmes::net::inet {

/** A mixin class to represent a wrapper for an IP transport protocol. */
class wrapper {
public:
	/** Get the transport layer protocol number for the payload.
	 * @param protocol the protocol number
	 */
	virtual uint8_t protocol() const = 0;

	/** Get the payload.
	 * @return the payload
	 */
	virtual octet::string payload() const = 0;
};

} /* namespace holmes::net::inet */

#endif
