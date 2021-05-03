// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ICMP_ECHO_MESSAGE
#define HOLMES_NET_ICMP_ECHO_MESSAGE

#include <cstdint>
#include <memory>
#include <vector>

#include "holmes/octet/string.h"
#include "holmes/net/icmp/message.h"

namespace holmes::net::icmp {

/** A class to represent an ICMP echo request or reply message.
 * This class is applicable to:
 * - ICMPv4 message types 0 and 8
 * - IVMPv6 message types 128 and 129
 */
class echo_message:
	public message {
public:
	/** Construct ICMP echo message.
	 * @param data the raw content
	 */
	explicit echo_message(const octet::string& data):
		message(data) {}

	/** Get the identification field.
	 * @return the identification field
	 */
	uint16_t id() const {
		return get_uint16(data(), 4);
	}

	/** Get the sequence number.
	 * @return the sequence number
	 */
	uint16_t seqnum() const {
		return get_uint16(data(), 6);
	}

	/** Get the payload.
	 * @return the payload
	 */
	octet::string payload() const {
		return data().substr(8);
	}

	bson::document to_bson() const override;
};

} /* namespace holmes::net::icmp */

#endif
