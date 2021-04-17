// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_BOOLEAN
#define HOLMES_BSON_BOOLEAN

#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent a boolean value. */
class boolean:
	public value {
private:
	/** The boolean value. */
	bool _value;
public:
	/** Construct BSON value containing boolean.
	 * @param value the required boolean value
	 */
	explicit boolean(bool value);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	/** Decode instance from octet string.
	 * @param bd the BSON data to be decoded
	 */
	static std::unique_ptr<boolean> decode(octet::string& bd);
};

} /* namespace holmes::bson */

#endif
