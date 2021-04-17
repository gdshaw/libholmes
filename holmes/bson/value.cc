// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/value.h"
#include "holmes/bson/boolean.h"
#include "holmes/bson/null.h"
#include "holmes/bson/int32.h"
#include "holmes/bson/int64.h"

namespace holmes::bson {

bool value::is_null() const {
	return false;
}

std::unique_ptr<value> value::decode(unsigned char type, octet::string& bd) {
	switch (type) {
	case 0x08:
		return bson::boolean::decode(bd);
	case 0x0a:
		return std::make_unique<null>();
	case 0x10:
		return bson::int32::decode(bd);
	case 0x12:
		return bson::int64::decode(bd);
	default:
		throw std::invalid_argument("unsupported BSON type code");
	}
}

} /* namespace holmes::bson */
