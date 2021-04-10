// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_PARSE_ERROR
#define HOLMES_PARSE_ERROR

#include <stdexcept>
#include <string>

namespace holmes {

/** A class to represent an error during parsing. */
class parse_error:
	public std::runtime_error {
public:
	/** Construct parse error.
	 * @param message a message describing the error
	 */
	explicit parse_error(const std::string& message);
};

} /* namespace holmes */

#endif
