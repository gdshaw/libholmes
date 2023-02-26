// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/binary.h"
#include "holmes/net/tcp/option.h"
#include "holmes/net/tcp/end_of_option_list.h"

namespace holmes::net::tcp {

using namespace bson;

option::option(octet::string& data) {
	uint8_t length = 1;
	try {
		uint8_t type = get_uint8(data, 0);
		if (type >= 2) {
			length = get_uint8(data, 1);
			if (length < 2) {
				length = 2;
			}
		}
	} catch (std::out_of_range&) {
		/* No action. */
	}
	_data = read(data, length);
}

bson::document option::to_bson() const {
	bson::document bson_option;
	bson_option.append("type", bson::int32(type()));
	bson_option.append("payload", bson::binary(payload()));
	return bson_option;
}

std::string option::name() const {
	return std::string();
}

std::unique_ptr<option> option::parse(octet::string& data) {
	switch (get_uint8(data, 0)) {
	case 0:
		return std::make_unique<end_of_option_list>(data);
	default:
		return std::make_unique<option>(data);
	}
}

} /* namespace holmes::net::tcp */
