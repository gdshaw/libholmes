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
class any;

/** An abstract base class to represent a BSON value of any type. */
class value {
public:
	/** A class for requesting that an octet::string be decoded as BSON. */
	class decode {};

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

	/** Test whether this value is null.
	 * @return true if null, otherwise false
	 */
	virtual bool is_null() const;

	/** Encode this value as BSON.
	 * @param bw a writer object to receive the BSON
	 */
	virtual void encode(writer& bw) const = 0;

	/** Encode this value as extended JSON.
	 * @return the encoded value
	 */
	virtual std::string to_json() const = 0;

	/** Resolve the underlying value.
	 * If this value is a reference to another value (as in the case of a
	 * bson::any) then return a reference to that underlying value,
	 * otherwise return a reference to this.
	 * @return the underlying bson::value
	 */
	virtual value& operator*();

	/** Resolve the underlying value.
	 * If this value is a reference to another value (as in the case of a
	 * bson::any) then return a reference to that underlying value,
	 * otherwise return a reference to this.
	 * @return the underlying bson::value
	 */
	virtual const value& operator*() const;

	/** Get the content of this BSON value if it is a boolean.
	 * @return the content
	 * @throws std::bad_cast if this is not a boolean
	 */
	virtual operator bool() const;

	/** Get the content of this BSON value if it is an integer.
	 * Allowed types are int32 and int64.
	 * @return the content
	 * @throws std::bad_cast if this is not an integer type
	 */
	virtual operator int64_t() const;

	/** Get the content of this BSON value if it is a character string.
	 * @return the content
	 * @throws std::bad_cast if this is not a character string
	 */
	virtual operator std::string() const;

	/** Get the content of this BSON value if it is a binary string.
	 * @return the content
	 * @throws std::bad_cast if this is not a binary string
	 */
	virtual operator octet::string() const;

	/** Dynamically cast this object to a sepcific type of bson::value.
	 * If this value is a reference to another value (as in the case of a
	 * bson::any) then return a cast reference to that underlying value,
	 * otherwise return a cast reference to this.
	 * @return a cast reference to the underlying value
	 * @throws std::bad_cast if the value is not of the expected type
	 */
	template<class T>
	T& as() {
		return dynamic_cast<T&>(**this);
	}

	/** Dynamically cast this object to a sepcific type of bson::value.
	 * If this value is a reference to another value (as in the case of a
	 * bson::any) then return a cast reference to that underlying value,
	 * otherwise return a cast reference to this.
	 * @return a cast reference to the underlying value
	 * @throws std::bad_cast if the value is not of the expected type
	 */
	template<class T>
	const T& as() const {
		return dynamic_cast<const T&>(**this);
	}

	/** Test whether this object can be dynamically cast to a given type
	 * @return true if it can be cast, otherwise false
	 */
	template<class T>
	bool is() const {
		return dynamic_cast<const T*>(&**this);
	}

	/** Get the single member corresponding to a given name.
	 * If this value is not a document then no name will match.
	 * @param name the name of the member
	 * @return the value of the member
	 * @throws std::out_of_range unless there is exactly one match
	 */
	virtual any& at(const std::string& name);

	/** Get the single member corresponding to a given name.
	 * If this value is not a document then no name will match.
	 * @param name the name of the member
	 * @return the value of the member
	 * @throws std::out_of_range unless there is exactly one match
	 */
	virtual const any& at(const std::string& name) const;

	/** Get the value corresponding to a given numeric index.
	 * If this value is not an array then no index will match.
	 * @param name the name of the member
	 * @return the value of the member
	 * @throws std::out_of_range if there is no member with that index
	 */
	virtual any& at(size_t index);

	/** Get the value corresponding to a given numeric index.
	 * If this value is not an array then no index will match.
	 * @param name the index of the member
	 * @return the value of the member
	 * @throws std::out_of_range if there is no member with that index
	 */
	virtual const any& at(size_t index) const;
};

} /* namespace holmes::bson */

#endif
