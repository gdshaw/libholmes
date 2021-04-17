// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_INT32
#define HOLMES_BSON_INT32

#include <cstdint>

#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent a 32-bit signed integer. */
class int32:
	public value {
private:
	/** The integer value. */
	int32_t _value;
public:
	/** Construct BSON value containing 32-bit integer.
	 * @param value the required integer value
	 */
	explicit int32(int32_t value);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	/** Get the value as an int32_t.
	 * @return the value
	 */
	int32_t as_int32() const {
		return _value;
	}

	/** Decode instance from octet string.
	 * @param bd the BSON data to be decoded
	 */
	static std::unique_ptr<int32> decode(octet::string& bd);
};

} /* namespace holmes::bson */

#endif
