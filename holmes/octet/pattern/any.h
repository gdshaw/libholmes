// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_ANY
#define HOLMES_OCTET_PATTERN_ANY

#include <memory>

#include "holmes/bson/value.h"
#include "holmes/octet/pattern/basic.h"

namespace holmes::octet::pattern {

/** A class to represent an octet pattern of any type. */
class any:
	public basic {
private:
	/** A pointer to a heap-allocated instance of the required pattern. */
	std::unique_ptr<basic> _pattern;
public:
	/** Construct pattern from BSON.
	 * @param bson_pattern the required pattern as BSON
	 */
	explicit any(const bson::value& bson_pattern);

	bool operator()(octet::string& octets) const override;
};

} /* namespace holmes::octet::pattern */

#endif
