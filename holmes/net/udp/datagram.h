// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_UDP_DATAGRAM
#define HOLMES_NET_UDP_DATAGRAM

#include "holmes/octet/string.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet/l4_packet.h"

namespace holmes::net::udp {

/** A class to represent a UDP datagram. */
class datagram:
	public inet::l4_packet {
public:
	/** The internet protocol number. */
	static const uint8_t protocol = 17;
private:
	/** The pseudo-header checksum. */
	inet::checksum _phc;

	/** The raw content. */
	octet::string _data;
public:
	/** Construct UDP datagram.
	 * @param inet_datagram the IP datagram to which this belongs.
	 * @param content the raw content of the datagram
	 */
	datagram(const inet::datagram& inet_datagram, octet::string& data);

	bson::document to_bson() const override;

	/** Get the source port.
	 * @return the source port
	 */
	uint16_t src_port() const override {
		return get_uint16(_data, 0);
	}

	/** Get the destination port.
	 * @return the destination port
	 */
	uint16_t dst_port() const override {
		return get_uint16(_data, 2);
	}

	/** Get the recorded checksum.
	 * @return the checksum
	 */
	uint16_t recorded_checksum() const {
		return get_uint16(_data, 6);
	}

	/** Get the calculated checksum.
	 * @return the calculated header checksum
	 */
	uint16_t calculated_checksum() const;

	/** Get the payload.
	 * @return the payload
	 */
	octet::string payload() const {
		return _data.substr(8);
	}
};

} /* namespace holmes::net::udp */

#endif
