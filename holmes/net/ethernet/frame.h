// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ETHERNET_FRAME
#define HOLMES_NET_ETHERNET_FRAME

#include <memory>
#include <cstdint>

#include "holmes/octet/string.h"
#include "holmes/artefact.h"
#include "holmes/net/ethernet/address.h"

namespace holmes::net::ethernet {

/** A class to represent an Ethernet frame. */
class frame:
	public artefact {
private:
	/** The raw content of this frame. */
	octet::string _data;

	/** The destination address. */
	mutable std::unique_ptr<address> _dst_addr;

	/** The source address. */
	mutable std::unique_ptr<address> _src_addr;
public:
	/** Construct ethernet frame.
	 * The raw content should include the header and the payload,
	 * but exclude the frame check sequence.
	 * @param data the raw content
	 */
	frame(octet::string data):
		_data(data) {}

	/** Get the destination address.
	 * @return the destination address
	 */
	const address& dst_addr() const {
		if (!_dst_addr) {
			auto dst_addr_data = _data.substr(0, 6);
			_dst_addr = std::make_unique<address>(dst_addr_data);
		}
		return *_dst_addr;
	}

	/** Get the source address.
	 * @return the source address
	 */
	const address& src_addr() const {
		if (!_src_addr) {
			auto src_addr_data = _data.substr(6, 6);
			_src_addr = std::make_unique<address>(src_addr_data);
		}
		return *_src_addr;
	}

	/** Get the ethertype.
	 * @return the ethertype
	 */
	uint16_t ethertype() const {
		return get_uint16(_data, 12);
	}

	/** Get the payload.
	 * Note that this may have been padded to 46 octets
	 * (depending on how the frame was captured).
	 * @return the payload
	 */
	octet::string payload() const {
		return _data.substr(14);
	}

	bson::document to_bson() const override;
};

} /* namespace holmes::net::ethernet */

#endif
