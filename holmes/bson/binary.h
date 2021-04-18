// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_BINARY
#define HOLMES_BSON_BINARY

#include <string>

#include "holmes/octet/string.h"
#include "holmes/bson/value.h"

namespace holmes::bson {

/** A BSON class to represent a binary string. */
class binary:
	public value {
private:
	/** The binary value. */
	octet::string _value;
public:
	/** Construct BSON value containing binary string.
	 * @param value the required binary value
	 */
	explicit binary(const octet::string& value);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	/** Get the value as an octet string.
	 * @return the value
	 */
	operator octet::string() const {
		return _value;
	}

	/** Decode instance from octet string.
	 * @param bd the BSON data to be decoded
	 */
	static std::unique_ptr<binary> decode(octet::string& bd);
};

} /* namespace holmes::bson */

#endif
