// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/binary.h"
#include "holmes/net/inet/checksum.h"
#include "holmes/net/icmp/message.h"
#include "holmes/net/icmp/echo_message.h"

namespace holmes::net::icmp {

uint16_t message::calculated_checksum() const {
	inet::checksum checksum;
	checksum(_data.substr(0, 2));
	checksum(_data.substr(4));
	return checksum;
}

bson::document message::to_bson() const {
	bson::document bson_checksum;
	bson_checksum.append("recorded", bson::int32(recorded_checksum()));
	bson_checksum.append("calculated", bson::int32(calculated_checksum()));

	bson::document bson_message;
	bson_message.append("type", bson::int32(type()));
	bson_message.append("code", bson::int32(code()));
	bson_message.append("checksum", bson_checksum);
	bson_message.append("raw_payload", bson::binary(raw_payload()));
	return bson_message;
}

std::unique_ptr<message> message::parse_icmp4(const octet::string& data) {
	switch (get_uint8(data, 0)) {
	case 0:
	case 8:
		return std::make_unique<echo_message>(data);
	default:
		return std::make_unique<message>(data);
	}
}

} /* namespace holmes::net::icmp */
