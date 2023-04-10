// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_HEX_DECODER
#define HOLMES_OCTET_HEX_DECODER

#include <cstddef>
#include <cstdint>

#include "holmes/octet/string.h"

namespace holmes::octet::hex {

/** A class for decoding hexadecimal strings.
 * Decoding is case-insensitive.
 */
class decoder {
private:
	/** The character set to be used for decoding. */
	static const int8_t _charset[];

	/** A buffer for any undecoded bits. */
	uint8_t _buffer = 0;

	/** The number of undecoded bits. */
	size_t _count = 0;
public:
	/** Decode a hex string to binary data.
	 * @param in the base64 string to be decoded
	 * @param final true to require that the input end on an octet
	 *  boundary, otherwise false
	 * @return the resulting binary data
	 */
	octet::string operator()(const std::string& in, bool final = true);
};

} /* namespace holmes::octet::hex */

#endif
