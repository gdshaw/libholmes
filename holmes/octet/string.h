// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_STRING
#define HOLMES_OCTET_STRING

#include <stdexcept>
#include <memory>
#include <cstddef>
#include <string>

#include "holmes/octet/buffer.h"

namespace holmes::octet {

/** A container class to represent a sequence of immutable octets.
 * The primary purpose of this class is to represent part or all of the raw
 * content of an artefact. It does not allow the underlying content to be
 * modified, however instances of this class can be modified so that they
 * refer to different content: either the full content of a different octet
 * string, or part of the content of the same or a different octet string.
 * These operations are performed in constant time (without physically
 * copying the underlying content).
 */
class string {
private:
	/** An octet buffer for use by the empty string. */
	static std::unique_ptr<buffer> _empty_buffer;
public:
	/** The type of an individual octet. */
	typedef unsigned char value_type;

	/** The type of a reference to an octet.
	 * Note that this is the same as a const_reference, since the content
	 * is immutable.
	 */
	typedef const value_type& reference;

	/** The type of a const reference to an octet. */
	typedef const value_type& const_reference;

	/** The type of a pointer to an octet.
	 * Note that this is the same as a const_pointer, since the content
	 * is immutable.
	 */
	typedef const value_type* pointer;

	/** The type of a const pointer to an octet. */
	typedef const value_type* const_pointer;

	/** The type of an iterator into an octet string.
	 * Note that this is the same as a const_iterator, since the content
	 * is immutable.
	 */
	typedef const_pointer iterator;

	/** The type of a const iterator into an octet string. */
	typedef const_pointer const_iterator;

	/** The type of a reverse iterator into an octet string.
	 * Note that this is the same as a const_reverse_iterator, since the
	 * content is immutable.
	 */
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/** The type of a const reverse iterator into an octet string. */
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	/** A type to represent a number of octets. */
	typedef size_t size_type;

	/** A type to represent a difference between two numbers of octets. */
	typedef ssize_t difference_type;

	/** The maximum permitted value of a size_type. */
	static const size_type npos = static_cast<size_type>(-1);
private:
	/** A pointer to an octet::buffer providing the content.
	 * This is used only for managing the lifetime of the buffer.
	 * It must not be null: if a buffer is not needed for storing the content
	 * then a dummy instance of an octet::buffer must be supplied instead.
	 */
	buffer* _buffer;

	/** A pointer to the first octet in the string.
	 * If _length == 0 then _data is undefined.
	 */
	const_pointer _data;

	/** The number of octets in the string. */
	size_type _length;
public:
	/** Construct an empty octet string. */
	string():
		_buffer(buffer::link(*_empty_buffer)),
		_length(0) {}

	/** Copy-construct an octet string.
	 * @param that the octet string to be copied
	 */
	string(const string& that):
		_buffer(buffer::link(*that._buffer)),
		_data(that._data),
		_length(that._length) {}

	/** Construct an octet string from a substring.
	 * If the requested substring would extend beyond the end of the
	 * available octets then its length is reduced accordingly.
	 * @param that the octet string from which to copy
	 * @param index the index of the first octet
	 * @param length the number of octets
	 */
	string(const string& that, size_type index, size_type length = npos);

	/** Construct an octet string from an octet buffer.
	 * The reference count of the buffer is not incremented, so must
	 * already have the appropriate value.
	 * @param buf the octet buffer containing the data
	 * @param data a pointer to the first octet
	 * @param length the number of octets
	 */
	string(buffer& buf, const_pointer data, size_type length):
		_buffer(&buf),
		_data(data),
		_length(length) {}

	/** Construct an octet string by copying from a pointer.
	 * @param data a pointer to the first octet
	 * @param length the number of octets
	 */
	string(const_pointer data, size_type length);

	/** Destroy this octet string. */
	~string() {
		buffer::unlink(*_buffer);
	}

	/** Copy-assign an octet string.
	 * @param that the octet string to be copied
	 */
	string& operator=(const string& that) {
		if (this != &that) {
			buffer::unlink(*this->_buffer);
			this->_buffer = buffer::link(*that._buffer);
			this->_data = that._data;
			this->_length = that._length;
		}
		return *this;
	}

	/** Get a const iterator to the start of the sequence.
	 * @return the iterator
	 */
	const_iterator begin() const {
		return _data;
	}

	/** Get a const iterator to the start of the sequence (alias).
	 * @return the iterator
	 */
	const_iterator cbegin() const {
		return _data;
	}

	/** Get a const iterator to the end of the sequence.
	 * @return the iterator
	 */
	const_iterator end() const {
		return _data + _length;
	}

	/** Get a const iterator to the end of the sequence (alias).
	 * @return the iterator
	 */
	const_iterator cend() const {
		return _data + _length;
	}

	/** Get a const iterator to the start of the reversed sequence.
	 * @return the reverse iterator
	 */
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}

	/** Get a const iterator to the start of the reversed sequence (alias).
	 * @return the reverse iterator
	 */
	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(end());
	}

	/** Get a const iterator to the end of the reversed sequence.
	 * @return the reverse iterator
	 */
	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

	/** Get a const iterator to the end of the reversed sequence (alias).
	 * @return the reverse iterator
	 */
	const_reverse_iterator crend() const {
		return const_reverse_iterator(begin());
	}

	/** Get a single octet (unchecked).
	 * @param index the index of the requested octet
	 * @return the requested octet
	 */
	value_type operator[](size_type index) const {
		return _data[index];
	}

	/** Get a single octet (checked).
	 * @param index the index of the requested octet
	 * @return the requested octet
	 */
	value_type at(size_type index) const {
		if (index >= _length) {
			throw std::out_of_range("out of range");
		}
		return _data[index];
	}

	/** Get the first octet (unchecked).
	 * @return the first octet
	 */
	value_type front() const {
		return _data[0];
	}

	/** Get the last octet (unchecked).
	 * @return the last octet
	 */
	value_type back() const {
		return _data[_length - 1];
	}

	/** Get a pointer to the content.
	 * @return a pointer to the content
	 */
	const_pointer data() const {
		return _data;
	}

	/** Test whether the octet string is empty.
	 * @return true if empty, otherwise false
	 */
	bool empty() const {
		return _length == 0;
	}

	/** Get the length.
	 * @return the length, in octets
	 */
	size_type length() const {
		return _length;
	}

	/** Get the length (alias).
	 * @return the length, in octets
	 */
	size_type size() const {
		return _length;
	}
};

} /* namespace holmes::octet */

#endif
