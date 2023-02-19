// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET6_DATAGRAM
#define HOLMES_NET_INET6_DATAGRAM

#include <cstdint>
#include <memory>
#include <vector>

#include "holmes/octet/string.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet6/address.h"

namespace holmes::net::inet6 {

/** A class to represent an IPv6 datagram. */
class datagram:
	public inet::datagram {
private:
	/** The raw content. */
	octet::string _data;

	/** The source address. */
	mutable std::unique_ptr<address> _src_addr;

	/** The destination address. */
	mutable std::unique_ptr<address> _dst_addr;
public:
	/** Construct IPv6 datagram.
	 * @param data the raw content of the datagram
	 */
	datagram(octet::string& data);

	const octet::string& data() const override {
		return _data;
	}

	/** Get the traffic class.
	 * @return the traffic class
	 */
	uint8_t traffic_class() const {
		return (get_uint16(_data, 4) >> 4) & 0xff;
	}

	/** Get the flow label.
	 * @return the flow label
	 */
	uint32_t flow_label() const {
		return get_uint32(_data, 0) & 0xfffff;
	}


	/** Get the payload length field.
	 * @return the payload length, in octets
	 */
	uint16_t payload_length() const {
		return get_uint16(_data, 4);
	}

	/** Get the next header protocol.
	 * @return the protocol number
	 */
	uint8_t next_header() const {
		return get_uint8(_data, 6);
	}

	/** Get the hop limit.
	 * @return the hop limit
	 */
	uint8_t hop_limit() const {
		return get_uint8(_data, 7);
	}

	const address& src_addr() const override {
		if (!_src_addr) {
			_src_addr = std::make_unique<address>(_data.substr(8, 16));
		}
		return *_src_addr;
	}

	const address& dst_addr() const override {
		if (!_dst_addr) {
			_dst_addr = std::make_unique<address>(_data.substr(24, 16));
		}
		return *_dst_addr;
	}

	/** Get the payload.
	 * @return the payload
	 */
	octet::string payload() const {
		return _data.substr(40);
	}

	bson::document to_bson() const override;
	inet::checksum make_pseudo_header_checksum(
		uint8_t protocol, size_t length) const override;
};

} /* namespace holmes::net::inet6 */

#endif
