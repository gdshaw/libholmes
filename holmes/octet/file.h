// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_FILE
#define HOLMES_OCTET_FILE

#include "holmes/octet/string.h"

namespace holmes::octet {

/** An octet string class to represent the mmaped content of a file.
 * The length of the mapping is fixed at the time of construction.
 */
class file:
	public string {
public:
	/** Construct octet file.
	 * @param pathname the pathname of the requested file
	 */
	explicit file(const std::string& pathname);
};

} /* namespace holmes::octet */

#endif
