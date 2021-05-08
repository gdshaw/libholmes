// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_BASIC
#define HOLMES_OCTET_PATTERN_BASIC

#include "holmes/octet/string.h"

namespace holmes::octet::pattern {

/** An abstract base class for matching a sequence of octets. */
class basic {
public:
	/** Test whether a given octet string matches this pattern.
	 * It is not necessary for the whole of the octet string to be match,
	 * however the match must begin at the start of the octet string.
	 *
	 * If the match was successful then the matching octets are removed
	 * from the start of the octet string. Otherwise, the resulting state
	 * of the octet string is unspecified.
	 * @param octets the octet string to be tested
	 * @return true if a match, otherwise false
	 */
	virtual bool operator()(octet::string& octets) const = 0;
};

} /* namespace holmes::octet::pattern */

#endif
