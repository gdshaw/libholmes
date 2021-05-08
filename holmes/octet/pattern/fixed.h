// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_PATTERN_FIXED
#define HOLMES_OCTET_PATTERN_FIXED

#include "holmes/bson/document.h"
#include "holmes/octet/pattern/basic.h"

namespace holmes::octet::pattern {

/** An octet pattern class to match fixed content.
 * The BSON representation of this class is a document with a type field
 * equal to "fixed" and a content field containing the required fixed
 * binary content.
 */
class fixed:
	public basic {
private:
	/** The content to be matched. */
	octet::string _content;
public:
	/** Construct fixed pattern from BSON.
	 * @param bson_pattern the required pattern as BSON
	 */
	explicit fixed(const bson::document& bson_pattern);

	bool operator()(octet::string& octets) const override;
};

} /* namespace holmes::octet::pattern */

#endif
