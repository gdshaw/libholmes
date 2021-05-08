// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_SEQUENCE
#define HOLMES_OCTET_PATTERN_SEQUENCE

#include <vector>

#include "holmes/bson/array.h"
#include "holmes/octet/pattern/basic.h"
#include "holmes/octet/pattern/any.h"

namespace holmes::octet::pattern {

/** An octet pattern class to match a sequence of other patterns.
 * The BSON representation of this class is an array containing the
 * required sub-patterns in the order they are to be matched.
 */
class sequence:
	public basic {
private:
	/** The sequence of patterns to be matched. */
	std::vector<octet::pattern::any> _patterns;
public:
	/** Construct sequence pattern from BSON.
	 * @param bson_pattern the required pattern as BSON
	 */
	explicit sequence(const bson::array& bson_pattern);

	bool operator()(octet::string& octets) const override;
};

} /* namespace holmes::octet::pattern */

#endif
