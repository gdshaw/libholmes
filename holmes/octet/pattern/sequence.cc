// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/pattern/sequence.h"

namespace holmes::octet::pattern {

sequence::sequence(const bson::array& bson_pattern) {
	for (auto& bson_subpattern : bson_pattern) {
		_patterns.push_back(octet::pattern::any(bson_subpattern));
	}
}

bool sequence::operator()(octet::string& octets) const {
	for (auto& pat : _patterns) {
		if (!pat(octets)) {
			return false;
		}
	}
	return true;
}

} /* namespace holmes::octet::pattern */
