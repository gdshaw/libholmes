// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_FIVE_TUPLE
#define HOLMES_NET_INET_FIVE_TUPLE

#include <memory>

#include "holmes/bson/document.h"
#include "holmes/net/inet/address.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet/l4_packet.h"

namespace holmes::net::inet {

/** A class to represent an Internet Protocol 5-tuple.
 * A 5-tuple uniquely identifies an Internet Protocol data flow.
 * It consists of:
 *
 * - The transport protocol number
 * - The destination IP address
 * - The destination port number
 * - The source IP address
 * - The source port number
 *
 * In this implementation, the components listed above are treated
 * as being in descending order of precendence.
 */
class five_tuple {
private:
	/** The transport protocol number. */
	uint8_t _protocol;

	/** The destination IP address. */
	std::unique_ptr<inet::address> _dst_addr;

	/** The destination port number. */
	uint16_t _dst_port;

	/** The source IP address. */
	std::unique_ptr<inet::address> _src_addr;

	/** The source port number. */
	uint16_t _src_port;
public:
	/** Construct 5-tuple.
	 * @param inet_dgram the IP datagram
	 * @param l4_afact the transport layer artefact
	 */
	five_tuple(const inet::datagram& inet_dgram,
		const inet::l4_packet& l4_pkt);

	/** Get the protocol number.
	 * @return the protocol number
	 */
	uint8_t protocol() const {
		return _protocol;
	}

	/** Get the destination IP address.
	 * @return the destination address
	 */
	const inet::address& dst_addr() const {
		return *_dst_addr;
	}

	/** Get the destination port number.
	 * @return the destination port number
	 */
	uint16_t dst_port() const {
		return _dst_port;
	}

	/** Get the source IP address.
	 * @return the source address
	 */
	const inet::address& src_addr() const {
		return *_src_addr;
	}

	/** Get the source port number.
	 * @return the source port number
	 */
	uint16_t src_port() const {
		return _src_port;
	}

	operator std::string() const;

	/** Describe this 5-tuple using BSON.
	 * @return a BSON description of this 5-tuple.
	 */
	bson::document to_bson() const;
};

bool operator==(const five_tuple& lhs, const five_tuple& rhs);
auto operator<=>(const five_tuple& lhs, const five_tuple& rhs);

} /* namespace holmes::net::inet */

#endif
