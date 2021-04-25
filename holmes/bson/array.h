// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_ARRAY
#define HOLMES_BSON_ARRAY

#include <memory>
#include <vector>

#include "holmes/bson/value.h"
#include "holmes/bson/any.h"

namespace holmes::bson {

/** A BSON class to represent an array. */
class array:
	public value {
public:
	/** Construct empty BSON array. */
	array() = default;

	/** Decode from an octet string.
	 * @param bd the BSON data to be decoded
	 * @param dec a flag to trigger decoding
	 */
	array(octet::string& bd, const decode& dec);

	/** The type of a member of the array. */
	typedef bson::any value_type;

	/** The type of a reference to a member. */
	typedef value_type& reference;

	/** The type of a const reference to a member. */
	typedef const value_type& const_reference;

	/** The type of an iterator. */
	typedef std::vector<value_type>::iterator iterator;

	/** The type of a const iterator. */
	typedef std::vector<value_type>::const_iterator const_iterator;

	/** The type of a reverse iterator. */
	typedef std::vector<value_type>::reverse_iterator reverse_iterator;

	/** The type of a const reverse iterator. */
	typedef std::vector<value_type>::const_reverse_iterator
		const_reverse_iterator;

	/** A type to represent the number of members. */
	typedef std::vector<value_type>::size_type size_type;

	/** A type to represent a difference between two numbers of members. */
	typedef std::vector<value_type>::difference_type difference_type;
private:
	/** The members of this array. */
	std::vector<value_type> _members;
public:
	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override ;

	any& at(size_t index) override;
	const any& at(size_t index) const override;

	/** Get an iterator to the start of this array.
	 * @return the iterator
	 */
	iterator begin() {
		return _members.begin();
	}

	/** Get a const iterator to the start of this array.
	 * @return the iterator
	 */
	const_iterator begin() const {
		return _members.begin();
	}

	/** Get a const iterator to the start of this array.
	 * @return the iterator
	 */
	const_iterator cbegin() const {
		return _members.cbegin();
	}

	/** Get an iterator to the end of this array.
	 * @return the iterator
	 */
	iterator end() {
		return _members.end();
	}

	/** Get a const iterator to the end of this array.
	 * @return the iterator
	 */
	const_iterator end() const {
		return _members.end();
	}

	/** Get a const iterator to the end of this array.
	 * @return the iterator
	 */
	const_iterator cend() const {
		return _members.cend();
	}

	/** Get a reverse iterator to the end of this array.
	 * @return the iterator
	 */
	reverse_iterator rbegin() {
		return _members.rbegin();
	}

	/** Get a const reverse iterator to the end of this array.
	 * @return the iterator
	 */
	const_reverse_iterator rbegin() const {
		return _members.rbegin();
	}

	/** Get a const reverse iterator to the end of this array.
	 * @return the iterator
	 */
	const_reverse_iterator crbegin() const {
		return _members.crbegin();
	}

	/** Get a reverse iterator to the start of this array.
	 * @return the iterator
	 */
	reverse_iterator rend() {
		return _members.rend();
	}

	/** Get a const reverse iterator to the start of this array.
	 * @return the iterator
	 */
	const_reverse_iterator rend() const {
		return _members.rend();
	}

	/** Get a const reverse iterator to the start of this array.
	 * @return the iterator
	 */
	const_reverse_iterator crend() const {
		return _members.crend();
	}

	/** Get the number of members of this array.
	 * @return the number of members
	 */
	size_t size() const {
		return _members.size();
	}

	/** Append a member to this array.
	 * @param value the value of the member
	 */
	void append(const bson::value& value);
};

} /* namespace holmes::bson */

#endif
