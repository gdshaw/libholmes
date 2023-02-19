// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <arpa/inet.h>

#include "holmes/bson/int32.h"
#include "holmes/bson/int64.h"
#include "holmes/bson/binary.h"
#include "holmes/bson/string.h"
#include "holmes/net/inet/checksum.h"
#include "holmes/net/inet6/datagram.h"

namespace holmes::net::inet6 {

datagram::datagram(octet::string& data) {
	size_t length = 40;
	try {
		length += get_uint16(data, 4);
	} catch (std::out_of_range&) {
		/* no action */
	}
	_data = read(data, length);
}

bson::document datagram::to_bson() const {
	bson::document bson_datagram;
	bson_datagram.append("version", bson::int32(version()));
	bson_datagram.append("traffic_class", bson::int32(traffic_class()));
	bson_datagram.append("flow_label", bson::int32(flow_label()));
	bson_datagram.append("payload_length", bson::int64(payload_length()));
	bson_datagram.append("next_header", bson::int32(next_header()));
	bson_datagram.append("hop_limit", bson::int32(hop_limit()));
	bson_datagram.append("src_addr", bson::string(src_addr()));
	bson_datagram.append("dst_addr", bson::string(dst_addr()));
	bson_datagram.append("payload", bson::binary(payload()));
	return bson_datagram;
}

inet::checksum datagram::make_pseudo_header_checksum(
	uint8_t protocol, size_t length) const {

        inet::checksum checksum;
        checksum(_data.substr(8, 32));
	checksum(length >> 16);
	checksum(length >> 0);
	checksum(0);
	checksum(protocol);
        return checksum;
}

} /* namespace holmes::net::inet6 */
