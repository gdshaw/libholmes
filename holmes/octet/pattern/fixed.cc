// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/bson/binary.h"
#include "holmes/octet/pattern/fixed.h"

namespace holmes::octet::pattern {

fixed::fixed(const bson::document& bson_pattern) {
	try {
		_content = bson_pattern.at("content");
	} catch (std::out_of_range&) {
		throw parse_error("missing content field in fixed pattern");
	} catch (std::bad_cast&) {
		throw parse_error("non-binary content in fixed pattern");
	}
}

bool fixed::operator()(octet::string& octets) const {
	size_t length = _content.length();
	if (octets.compare(0, length, _content) != 0) {
		return false;
	}
	octets.remove_prefix(length);
	return true;
}

} /* namespace holmes::octet::pattern */
