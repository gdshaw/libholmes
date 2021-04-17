// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_UNICODE_UTF8_DECODER
#define HOLMES_UNICODE_UTF8_DECODER

#include <cstdint>

#include "holmes/octet/string.h"

namespace holmes::unicode::utf8 {

/** A class for decoding UTF-8. */
class decoder {
private:
	/** The remaining data. */
	octet::string _data;
public:
	/** Construct UTF-8 decoder.
	 * @param data the octet string to be decoded
	 */
	explicit decoder(const octet::string& data);

	/** Determine whether there is data which has not been decoded.
	 * Note that a return value of true does not imply that any further
	 * code points can be successfully decoded.
	 * @return true if data remaining, otherwise false
	 */
	operator bool() const {
		return !_data.empty();
	}

	/** Decode the next code point.
	 * @return a Unicode code point
	 */
	uint32_t operator()();
};

} /* namespace holmes::unicode::utf8 */

#endif
