// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_INT64
#define HOLMES_BSON_INT64

#include <cstdint>

#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent a 64-bit signed integer. */
class int64:
	public value {
private:
	/** The integer value. */
	int64_t _value;
public:
	/** Construct BSON value containing 64-bit integer.
	 * @param value the required integer value
	 */
	explicit int64(int64_t value);

	/** Decode from an octet string.
	 * @param bd the BSON data to be decoded
	 * @param dec a flag to trigger decoding
	 */
	explicit int64(octet::string& bd, const decode& dec);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	/** Get the value as an int64_t.
	 * @return the value
	 */
	int64_t as_int64() const {
		return _value;
	}
};

} /* namespace holmes::bson */

#endif
