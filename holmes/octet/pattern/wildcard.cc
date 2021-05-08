// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/octet/pattern/wildcard.h"

namespace holmes::octet::pattern {

wildcard::wildcard(const bson::document& bson_pattern) {
	try {
		int64_t length = bson_pattern.at("length");
		if (length < 0) {
			throw parse_error("negative length in wildcard pattern");
		}
		_length = length;
	} catch (std::out_of_range&) {
		throw parse_error("missing length in wildcard pattern");
	}
}

bool wildcard::operator()(octet::string& octets) const {
	if (octets.length() < _length) {
		return false;
	}
	octets.remove_prefix(_length);
	return true;
}

} /* namespace holmes::octet::pattern */
