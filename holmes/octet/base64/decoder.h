// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_BASE64_DECODER
#define HOLMES_OCTET_BASE64_DECODER

#include <cstddef>
#include <cstdint>

#include "holmes/octet/string.h"

namespace holmes::octet::base64 {

/** A class for performing base64 decoding.
 * Decoding is performed using the standard base64 alphabet as defined
 * by RFC 4648, with padding characters.
 */
class decoder {
private:
	/** The character set to be used for decoding. */
	static const int8_t _charset[];

	/** A buffer for any undecoded bits. */
	unsigned int _buffer = 0;

	/** The number of undecoded bits. */
	size_t _count = 0;
public:
	/** Decode a base-64 string to binary data.
	 * @param in the base64 string to be decoded
	 * @return the resulting binary data
	 */
	octet::string operator()(const std::string& in);
};

} /* namespace holmes::octet::base64 */

#endif
