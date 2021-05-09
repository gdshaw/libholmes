// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ICMP_ECHO_SIGNATURE
#define HOLMES_NET_ICMP_ECHO_SIGNATURE

#include <optional>

#include "holmes/octet/pattern/any.h"
#include "holmes/net/icmp/echo/message.h"

namespace holmes::net::icmp::echo {

/** A class to represent a signature for classifying ICMP echo messages. */
class signature {
private:
	/** An optional identification field to be matched. */
	std::optional<uint16_t> _id;

	/** An optional sequence number to be matched. */
	std::optional<uint16_t> _seqnum;

    /** An optional pattern to be matched by the payload. */
	std::optional<octet::pattern::any> _payload;
public:
	/** Construct ICMP echo signature.
	 * @param bson the signature as BSON
	 */
	explicit signature(const bson::document& bson_sig);

	/** Test whether a given ICMP echo message matches this signature.
	 * @param msg the message to be tested
	 * @return true if signature matched, otherwise false
	 */
	bool operator()(const icmp::echo::message& msg) const;
};

} /* namespace holmes::net::icmp::echo */

#endif
