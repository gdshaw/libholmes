// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/binary.h"
#include "holmes/bson/document.h"
#include "holmes/net/inet/checksum.h"
#include "holmes/net/udp/datagram.h"

namespace holmes::net::udp {

using namespace bson;

datagram::datagram(const inet::datagram& inet_datagram, octet::string& data):
	_phc(inet_datagram.make_pseudo_header_checksum(protocol, data.length())) {

	size_t length = 0;
	try {
		length = get_uint16(data, 4);
	} catch (std::out_of_range&) {
		/* no action */
	}
	if (length < 8) {
		length = 8;
	}
	_data = read(data, length);
}

bson::document datagram::to_bson() const {
	bson::document bson_checksum;
	bson_checksum.append("recorded", bson::int32(recorded_checksum()));
	bson_checksum.append("calculated", bson::int32(calculated_checksum()));

	bson::document bson_datagram;
	bson_datagram.append("src_port", bson::int32(src_port()));
	bson_datagram.append("dst_port", bson::int32(dst_port()));
	bson_datagram.append("checksum", bson_checksum);
	bson_datagram.append("payload", bson::binary(payload()));
	return bson_datagram;
}

uint16_t datagram::calculated_checksum() const {
	inet::checksum checksum = _phc;
	checksum(_data.substr(0, 6));
	checksum(_data.substr(8));
	return checksum;
}

} /* namespace holmes::net::udp */
