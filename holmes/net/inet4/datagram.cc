// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/boolean.h"
#include "holmes/bson/string.h"
#include "holmes/bson/binary.h"
#include "holmes/bson/array.h"
#include "holmes/net/inet/checksum.h"
#include "holmes/net/inet4/datagram.h"

namespace holmes::net::inet4 {

datagram::datagram(octet::string& data) {
	size_t length = 20;
	try {
		length = get_uint16(data, 2);
	} catch (std::out_of_range&) {
		/* no action */
	}
	_data = read(data, length);
}

std::unique_ptr<datagram::option_list> datagram::_make_options() const {
	octet::string header = _data.substr(0, ihl() * 4);
	octet::string option_data = header.substr(20);

	std::unique_ptr<option_list> options = std::make_unique<option_list>();
	while (!option_data.empty()) {
		std::unique_ptr<option> opt = option::parse(option_data);
		bool eool = (opt->type() == 0);
		options->push_back(std::move(opt));
		if (eool) {
			break;
		}
	}
	return options;
}

uint16_t datagram::calculated_checksum() const {
	inet::checksum checksum;
	checksum(_data.substr(0, 10));
	checksum(_data.substr(12, ihl() * 4 - 12));
	return checksum;
}

bson::document datagram::to_bson() const {
	bson::document bson_checksum;
	bson_checksum.append("recorded", bson::int32(recorded_checksum()));
	bson_checksum.append("calculated", bson::int32(calculated_checksum()));

	bson::array bson_options;
	for (const auto& option : options()) {
		bson_options.append(option->to_bson());
	}

	bson::document bson_datagram;
	bson_datagram.append("version", bson::int32(version()));
	bson_datagram.append("ihl", bson::int32(ihl()));
	bson_datagram.append("tos", bson::int32(tos()));
	bson_datagram.append("length", bson::int32(length()));
	bson_datagram.append("id", bson::int32(id()));
	bson_datagram.append("evil", bson::boolean(evil()));
	bson_datagram.append("df", bson::boolean(df()));
	bson_datagram.append("mf", bson::boolean(mf()));
	bson_datagram.append("frag", bson::int32(frag()));
	bson_datagram.append("ttl", bson::int32(ttl()));
	bson_datagram.append("protocol", bson::int32(protocol()));
	bson_datagram.append("checksum", bson_checksum);
	bson_datagram.append("src_addr", bson::string(src_addr()));
	bson_datagram.append("dst_addr", bson::string(dst_addr()));
	bson_datagram.append("options", bson_options);
	bson_datagram.append("payload", bson::binary(payload()));
	return bson_datagram;
}

inet::checksum datagram::make_pseudo_header_checksum() const {
	inet::checksum checksum;
	checksum(_data.substr(12, 8));
	checksum(protocol());
	checksum(payload().length());
	return checksum;
}

} /* namespace holmes::net::inet4 */
