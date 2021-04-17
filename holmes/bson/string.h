// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_STRING
#define HOLMES_BSON_STRING

#include <string>

#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent a UTF-8 string. */
class string:
	public value {
private:
	/** The string value. */
	std::string _value;
public:
	/** Construct BSON value containing UTF-8 string.
	 * @param value the required string value
	 */
	explicit string(const std::string& value);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	/** Decode instance from octet string.
	 * @param bd the BSON data to be decoded
	 */
	static std::unique_ptr<string> decode(octet::string& bd);
};

} /* namespace holmes::bson */

#endif
