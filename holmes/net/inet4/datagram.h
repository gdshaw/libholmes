// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET4_DATAGRAM
#define HOLMES_NET_INET4_DATAGRAM

#include <cstdint>
#include <memory>
#include <vector>

#include "holmes/octet/string.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet4/address.h"
#include "holmes/net/inet4/option.h"

namespace holmes::net::inet4 {

/** A class to represent an IPv4 datagram. */
class datagram:
	public inet::datagram {
private:
	/** A type to represent a list of options. */
	typedef std::vector<std::unique_ptr<option>> option_list;

	/** The raw content. */
	octet::string _data;

	/** The source address. */
	mutable std::unique_ptr<address> _src_addr;

	/** The destination address. */
	mutable std::unique_ptr<address> _dst_addr;

	/** The list of options. */
	mutable std::unique_ptr<option_list> _options;

	/** Make the list of options.
	 * @return the newly-created list of options
	 */
	std::unique_ptr<option_list> _make_options() const;
public:
	/** Construct IPv4 datagram.
	 * @param data a source of raw content
	 */
	explicit datagram(octet::string& data);

	const octet::string& data() const override {
		return _data;
	}

	/** Get the internet header length.
	 * @return the header length, in 32-bit words.
	 */
	unsigned int ihl() const {
		return get_uint8(_data, 0) & 0xf;
	}

	/** Get the type of service field.
	 * @return the type of service
	 */
	uint8_t tos() const {
		return get_uint8(_data, 1);
	}

	/** Get the total length field.
	 * @return the total length, in octets
	 */
	uint16_t length() const {
		return get_uint16(_data, 2);
	}

	/** Get the identification field.
	 * @return the identification field
	 */
	uint16_t id() const {
		return get_uint16(_data, 4);
	}

	/** Get the evil bit.
	 * Following RFC 3514, in the absence of any other interpretation
	 * for a non-zero value.
	 * @return true if datagram declared malicious, otherwise false
	 */
	bool evil() const {
		return _data.at(6) & 0x80;
	}

	/** Get the do not fragment flag.
	 * @return true if datagram should not be fragmented, otherwise false
	 */
	bool df() const {
		return _data.at(6) & 0x40;
	}

	/** Get the more fragments flag.
	 * @return true if more fragments follow, otherwise false
	 */
	bool mf() const {
		return _data.at(6) & 0x20;
	}

	/** Get the fragment offset.
	 * @return the fragment offset (excluding flags)
	 */
	uint16_t frag() const {
		return get_uint16(_data, 6) & 0x1fff;
	}

	/** Get the time to live.
	 * @return the time to live
	 */
	uint8_t ttl() const {
		return get_uint8(_data, 8);
	}

	/** Get the next layer protocol.
	 * @return the protocol number
	 */
	uint8_t protocol() const {
		return get_uint8(_data, 9);
	}

	/** Get the recorded header checksum.
	 * @return the checksum
	 */
	uint16_t recorded_checksum() const {
		return get_uint16(_data, 10);
	}

	/** Get the calculated header checksum.
	 * This is the checksum as calculated by summing every word in the
	 * header except for the checksum field.
	 * @return the calculated header checksum
	 */
	uint16_t calculated_checksum() const;

	const address& src_addr() const override {
		if (!_src_addr) {
			_src_addr = std::make_unique<address>(_data.substr(12, 4));
		}
		return *_src_addr;
	}

	const address& dst_addr() const override {
		if (!_dst_addr) {
			_dst_addr = std::make_unique<address>(_data.substr(16, 4));
		}
		return *_dst_addr;
	}

	/** Get the list of options.
	 * @return the list of options
	 */
	const option_list& options() const {
		if (!_options) {
			_options = _make_options();
		}
		return *_options;
	}

	/** Get the payload.
	 * @return the payload
	 */
	octet::string payload() const {
		return _data.substr(ihl() * 4);
	}

	bson::document to_bson() const override;
	inet::checksum make_pseudo_header_checksum(
		uint8_t protocol, size_t length) const override;
};

} /* namespace holmes::net::inet4 */

#endif
