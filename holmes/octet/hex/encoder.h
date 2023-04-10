// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_HEX_ENCODER
#define HOLMES_OCTET_HEX_ENCODER

#include <cstddef>

#include "holmes/octet/string.h"

namespace holmes::octet::hex {

/** A class for encoding hexadecimal strings. */
class encoder {
private:
	/** The character set to be used for encoding. */
	static const char* _charset;
public:
	/** Encode binary data as a hexadecimal string.
	 * @param in the binary data to be encoded
	 * @return the hexadecimal string
	 */
	std::string operator()(const octet::string& in);
};

} /* namespace holmes::octet::base64 */

#endif
