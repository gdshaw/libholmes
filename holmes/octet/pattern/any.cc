// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/octet/pattern/any.h"
#include "holmes/octet/pattern/fixed.h"
#include "holmes/octet/pattern/timeval.h"
#include "holmes/octet/pattern/wildcard.h"
#include "holmes/octet/pattern/sequence.h"
#include "holmes/bson/string.h"
#include "holmes/bson/document.h"
#include "holmes/bson/array.h"

namespace holmes::octet::pattern {

any::any(const bson::value& bson_pattern) {
	if (bson_pattern.is<bson::document>()) {
		const auto& document = bson_pattern.as<bson::document>();
		std::string type(document.at("type"));
		if (type == "fixed") {
			_pattern = std::make_unique<pattern::fixed>(document);
		} else if (type == "timeval") {
			_pattern = std::make_unique<pattern::timeval>(document);
		} else if (type == "wildcard") {
			_pattern = std::make_unique<pattern::wildcard>(document);
		} else {
			throw parse_error("unrecognised pattern type");
		}
	} else if (bson_pattern.is<bson::array>()) {
		_pattern = std::make_unique<pattern::sequence>(bson_pattern.as<bson::array>());
	} else {
		throw parse_error("invalid BSON type for octet pattern.");
	}
}

bool any::operator()(octet::string& octets) const {
	return _pattern->operator()(octets);
}

} /* namespace holmes::octet::pattern */
