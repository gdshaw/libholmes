// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/value.h"

namespace holmes::bson {

std::unique_ptr<value> value::decode(unsigned char type, octet::string& bd) {
	throw std::invalid_argument("unsupported BSON type code");
}

} /* namespace holmes::bson */
