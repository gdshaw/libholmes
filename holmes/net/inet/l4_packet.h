// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_L4_PACKET
#define HOLMES_NET_INET_L4_PACKET

#include "holmes/artefact.h"

namespace holmes::net::inet {

/** A class to represent an IP transport layer packet. */
class l4_packet:
	public artefact {
public:
	/** Get the source port number.
	 * @return the source port number, or 0 if not applicable
	 */
	virtual uint16_t src_port() const = 0;

	/** Get the destination port number.
	 * @return the destination port number, or 0 if not applicable
	 */
	virtual uint16_t dst_port() const = 0;
};

} /* namespace holmes::net::inet */

#endif
