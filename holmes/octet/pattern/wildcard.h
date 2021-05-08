// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_WILDCARD
#define HOLMES_OCTET_PATTERN_WILDCARD

#include "holmes/bson/document.h"
#include "holmes/octet/pattern/basic.h"

namespace holmes::octet::pattern {

/** An octet pattern class to match arbitrary content.
 * The BSON representation of this class is a document with the following
 * fields:
 * - "type": "wildcard"
 * - "length": the number of octets to be matched
 */
class wildcard:
	public basic {
private:
	/** The number of octets to be matched. */
	size_t _length;
public:
	/** Construct wildcard pattern from BSON.
	 * @param bson_pattern the required pattern as BSON
	 */
	explicit wildcard(const bson::document& bson_pattern);

	bool operator()(octet::string& octets) const override;
};

} /* namespace holmes::octet::pattern */

#endif
