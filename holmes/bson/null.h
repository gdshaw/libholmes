// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_NULL
#define HOLMES_BSON_NULL

#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent the null value. */
class null:
	public value {
public:
	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	bool is_null() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;
};

} /* namespace holmes::bson */

#endif
