// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_BASE64_ENCODER
#define HOLMES_OCTET_BASE64_ENCODER

#include <cstddef>

#include "holmes/octet/string.h"

namespace holmes::octet::base64 {

/** A class for performing base64 encoding.
 * Encoding is performed using the standard base64 alphabet as defined
 * by RFC 4648, with padding characters.
 */
class encoder {
private:
	/** The character set to be used for encoding. */
	static const char* _charset;

	/** A buffer for any unencoded bits. */
	unsigned int _buffer = 0;

	/** The number of unencoded bits. */
	size_t _count = 0;
public:
	/** Encode binary data as a base-64 string.
	 * @param in the binary data to be encoded
	 * @param final true if no further data, otherwise false
	 * @return the base64 string
	 */
	std::string operator()(const octet::string& in, bool final);
};

} /* namespace holmes::octet::base64 */

#endif
