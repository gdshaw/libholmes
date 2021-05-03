// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ICMP_MESSAGE
#define HOLMES_NET_ICMP_MESSAGE

#include <cstdint>
#include <memory>
#include <vector>

#include "holmes/artefact.h"
#include "holmes/octet/string.h"

namespace holmes::net::icmp {

/** A class to represent an ICMP message. */
class message:
	public artefact {
private:
	/** The raw content. */
	octet::string _data;
public:
	/** Construct ICMP message.
	 * @param data the raw content
	 */
	explicit message(const octet::string& data):
		_data(data) {}

	/** Get the raw content of this message.
	 * @return the raw content
	 */
	const octet::string& data() const {
		return _data;
	}

	/** Get the message type.
	 * @return the message type
	 */
	unsigned int type() const {
		return get_uint8(_data, 0);
	}

	/** Get the message code.
	 * @return the message code
	 */
	unsigned int code() const {
		return get_uint8(_data, 1);
	}

	/** Get the recorded checksum.
	 * @return the checksum
	 */
	uint16_t recorded_checksum() const {
		return get_uint16(_data, 2);
	}

	/** Get the calculated checksum.
	 * This is the checksum as calculated by summing every word in the
	 * message except for the checksum field.
	 * @return the calculated header checksum
	 */
	uint16_t calculated_checksum() const;

	/** Get the raw payload.
	 * @return the undecoded payload of this ICMP message
	 */
	octet::string raw_payload() const {
		return _data.substr(4);
	}

	bson::document to_bson() const override;

	/** Parse an ICMPv4 option.
	 * @param data a source of raw content
	 * @return the resulting option
	 */
	static std::unique_ptr<message> parse_icmp4(const octet::string& data);
};

} /* namespace holmes::net::icmp */

#endif
