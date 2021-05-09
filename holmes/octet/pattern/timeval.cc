// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/octet/pattern/timeval.h"

namespace holmes::octet::pattern {

timeval::timeval(const holmes::bson::document& bson_pattern) {
	try {
		int64_t width = bson_pattern.at("width");
		if (width < 0) {
			throw parse_error("negative width in timeval pattern");
		}
		_width = width;
	} catch (std::out_of_range&) {
		throw parse_error("missing width in timeval pattern");
	}
	if ((_width !=32) && (_width != 64)) {
		throw parse_error("unsupported width in timeval pattern");
	}
	try {
		// Allow value to wrap around if negative.
		int64_t byte_order = bson_pattern.at("byte_order");
		_byte_order = byte_order;
	} catch (std::out_of_range&) {
		throw parse_error("missing byte_order in timeval pattern");
	}
}

bool timeval::operator()(octet::string& octets) const {
	int64_t sec;
	int64_t usec;
	if (_width == 64) {
		if (octets.length() < 16) {
			return false;
		}
		sec = read_int64(octets, _byte_order);
		usec = read_int64(octets, _byte_order);
	} else {
		if (octets.length() < 8) {
			return false;
		}
		sec = read_int32(octets, _byte_order);
		usec = read_int32(octets, _byte_order);
	}
	if ((usec < 0) || (usec > 999999)) {
		return false;
	}
	return true;
}

} /* namespace holmes::octet::pattern */
