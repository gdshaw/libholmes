// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_TIMEVAL
#define HOLMES_OCTET_PATTERN_TIMEVAL

#include "holmes/bson/document.h"
#include "holmes/octet/pattern/basic.h"

namespace holmes::octet::pattern {

/** An octet pattern class to match a struct timeval.
 * The BSON representation of this class is a document with the following
 * fields:
 * - "type": "timeval"
 * - "width": the word size, in bits
 * - "byte_order": the byte order mask
 *
 * Current policy is to accept any time, however implausible, provided that
 * it is well-formed.
 */
class timeval:
	public basic {
private:
	/** The word size, in bits. */
	unsigned int _width;

	/** The byte order mask. */
	unsigned int _byte_order;
public:
	/** Construct timeval pattern from BSON.
	 * @param bson_pattern the required pattern as BSON
	 */
	explicit timeval(const bson::document& bson_pattern);

	bool operator()(octet::string& octets) const override;
};

} /* namespace holmes::octet::pattern */

#endif
