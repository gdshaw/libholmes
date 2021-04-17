// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/null.h"

namespace holmes::bson {

std::unique_ptr<value> null::clone() const {
	return std::make_unique<null>();
}

unsigned char null::type() const {
	return 0x0a;
}

size_t null::length() const {
	return 0;
}

bool null::is_null() const {
	return true;
}

void null::encode(writer& bw) const {}

std::string null::to_json() const {
	return "null";
}

} /* namespace holmes::bson */
