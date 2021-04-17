// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_VALUE
#define HOLMES_BSON_VALUE

#include <cstddef>
#include <memory>
#include <string>

#include "holmes/octet/string.h"

namespace holmes::bson {

class writer;

/** An abstract base class to represent a BSON value of any type. */
class value {
public:
	virtual ~value() = default;

	/** Make a copy of this BSON value with the same dynamic type.
	 * @return a copy of this value
	 */
	virtual std::unique_ptr<value> clone() const = 0;

	/** Get the type code for this value.
	 * @return the type code
	 */
	virtual unsigned char type() const = 0;

	/** Get the encoded length of this value.
	 * @return the length, in octets
	 */
	virtual size_t length() const = 0;

	/** Encode this value as BSON.
	 * @param bw a writer object to receive the BSON
	 */
	virtual void encode(writer& bw) const = 0;

	/** Encode this value as extended JSON.
	 * @return the encoded value
	 */
	virtual std::string to_json() const = 0;

	/** Decode a value from an octet string.
	 * @param type the required object type
	 * @param bd the BSON data to be decoded
	 * @return the resulting BSON value
	 */
	static std::unique_ptr<value> decode(unsigned char type,
		octet::string& bd);
};

} /* namespace holmes::bson */

#endif
