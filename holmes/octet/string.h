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
#include <iostream>

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

	/** Construct an octet string by copying from a std::basic_string.
	 * @param that the std::basic_string from which to copy
	 */
	string(const std::basic_string<unsigned char>& that);

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

	/** Remove octets from start of string (unchecked).
	 * @param count the number of octets to remove
	 */
	void remove_prefix(size_type count) {
		_data += count;
		_length -= count;
	}

	/** Remove octets from end of string (unchecked).
	 * @param count the number of octets to remove
	 */
	void remove_suffix(size_type count) {
		_length -= count;
	}

	/** Swap content with another octet string.
	 * @param that the octet string with which to swap
	 */
	void swap(string& that) {
		std::swap(this->_buffer, that._buffer);
		std::swap(this->_data, that._data);
		std::swap(this->_length, that._length);
	}

	/** Construct a substring.
	 * If the requested substring would extend beyond the end of the
	 * available octets then its length is reduced accordingly.
	 * @param index the index of the first octet
	 * @param length the number of octets
	 */
	string substr(size_type index, size_type length = npos) const {
		return string(*this, index, length);
	}

	/** Lexicographically compare with another octet string.
	 * @param that the octet string to compare against
	 * @return -1 if this lower, 0 if equal, +1 if greater
	 */
	int compare(const octet::string& that) const;

	/** Lexicographically compare substring with another octet string.
	 * @param index the index of the first octet to take from this
	 * @param length the number of octets to take from this
	 * @param that the octet string to compare against
	 * @return -1 if this lower, 0 if equal, +1 if greater
	 */
	int compare(size_type index, size_type length,
		const octet::string& that) const {

		return substr(index, length).compare(that);
	}

	/** Lexicographically compare substring with another octet substring
	 * @param index the index of the first octet to take from this
	 * @param length the number of octets to take from this
	 * @param that the octet string to compare against
	 * @param index2 the index of the first octet to take from that
	 * @param length2 the number of octets to take from that
	 * @return -1 if this lower, 0 if equal, +1 if greater
	 */
	int compare(size_type index, size_type length,
		const octet::string& that,
		size_type index2, size_type length2) const {

		return substr(index, length).compare(that.substr(index2, length2));
	}
};

inline bool operator==(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) == 0;
}

inline bool operator!=(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) != 0;
}

inline bool operator<(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) < 0;
}

inline bool operator>=(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) >= 0;
}

inline bool operator<=(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) <= 0;
}

inline bool operator>(const octet::string& lhs, const octet::string& rhs) {
	return lhs.compare(rhs) > 0;
}

/** Write an octet string as hex to an output stream.
 * Each octet is converted to a pair of hex digits. Where there is a choice
 * between upper and lower case, this is determined by the stream state.
 * No whitespace or other characters are added, regardless of the length of
 * the octet string.
 * @param out the output stream
 * @param octets the octet string
 * @return the output stream
 */
std::ostream& operator<<(std::ostream& out, const string& octets);

/** Get an unsigned 8-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint8_t get_uint8(const string& octets, string::size_type index) {
	return octets.at(index);
}

/** Get an unsigned 16-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint16_t get_uint16(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(index + 1);
	auto data = octets.data() + index;
	byte_order &= 1;
	uint16_t result = data[0 ^ byte_order];
	result <<= 8;
	result |= data[1 ^ byte_order];
	return result;
}

/** Get an unsigned 32-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint32_t get_uint32(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(3);
	byte_order &= 3;
	auto data = octets.data() + index;
	uint32_t result = data[0 ^ byte_order];
	result <<= 8;
	result |= data[1 ^ byte_order];
	result <<= 8;
	result |= data[2 ^ byte_order];
	result <<= 8;
	result |= data[3 ^ byte_order];
	return result;
}

/** Get an unsigned 64-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint64_t get_uint64(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(7);
	byte_order &= 7;
	auto data = octets.data() + index;
	uint64_t result = data[0 ^ byte_order];
	result <<= 8;
	result |= data[1 ^ byte_order];
	result <<= 8;
	result |= data[2 ^ byte_order];
	result <<= 8;
	result |= data[3 ^ byte_order];
	result <<= 8;
	result |= data[4 ^ byte_order];
	result <<= 8;
	result |= data[5 ^ byte_order];
	result <<= 8;
	result |= data[6 ^ byte_order];
	result <<= 8;
	result |= data[7 ^ byte_order];
	return result;
}

/** Get a signed 8-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int8_t get_int8(const string& octets, string::size_type index) {
	// An int16_t is needed here because the intermediate result
	// would be too large to fit into an int8_t.
	int16_t result = octets.at(index);
	result = (result & 0x7f) - (result & 0x80);
	return result;
}

/** Get a signed 16-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int16_t get_int16(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(1);
	byte_order &= 1;
	auto data = octets.data() + index;
	int16_t result = data[0 ^ byte_order];
	result = (result & 0x7f) - (result & 0x80);
	result <<= 8;
	result |= data[1 ^ byte_order];
	return result;
}

/** Get a signed 32-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int32_t get_int32(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(3);
	byte_order &= 3;
	auto data = octets.data() + index;
	int32_t result = data[0 ^ byte_order];
	result = (result & 0x7f) - (result & 0x80);
	result <<= 8;
	result |= data[1 ^ byte_order];
	result <<= 8;
	result |= data[2 ^ byte_order];
	result <<= 8;
	result |= data[3 ^ byte_order];
	return result;
}

/** Get a signed 64-bit integer from an octet string.
 * @param octets the octet string
 * @param index an index into the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int64_t get_int64(const string& octets,
	string::size_type index, unsigned int byte_order = 0) {

	octets.at(7);
	byte_order &= 7;
	auto data = octets.data() + index;
	int64_t result = data[0 ^ byte_order];
	result = (result & 0x7f) - (result & 0x80);
	result <<= 8;
	result |= data[1 ^ byte_order];
	result <<= 8;
	result |= data[2 ^ byte_order];
	result <<= 8;
	result |= data[3 ^ byte_order];
	result <<= 8;
	result |= data[4 ^ byte_order];
	result <<= 8;
	result |= data[5 ^ byte_order];
	result <<= 8;
	result |= data[6 ^ byte_order];
	result <<= 8;
	result |= data[7 ^ byte_order];
	return result;
}

/** Read an unsigned 8-bit integer from an octet string.
 * @param octets the octet string
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint8_t read_uint8(string& octets) {
	auto result = get_uint8(octets, 0);
	octets.remove_prefix(1);
	return result;
}

/** Read a signed 8-bit integer from an octet string.
 * @param octets the octet string
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int8_t read_int8(string& octets) {
	auto result = get_int8(octets, 0);
	octets.remove_prefix(1);
	return result;
}

/** Read an unsigned 16-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint16_t read_uint16(string& octets, unsigned int byte_order = 0) {
	auto result = get_uint16(octets, 0, byte_order);
	octets.remove_prefix(2);
	return result;
}

/** Read a signed 16-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int16_t read_int16(string& octets, unsigned int byte_order = 0) {
	auto result = get_int16(octets, 0, byte_order);
	octets.remove_prefix(2);
	return result;
}

/** Read an unsigned 32-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint32_t read_uint32(string& octets, unsigned int byte_order = 0) {
	auto result = get_uint32(octets, 0, byte_order);
	octets.remove_prefix(4);
	return result;
}

/** Read a signed 32-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int32_t read_int32(string& octets, unsigned int byte_order = 0) {
	auto result = get_int32(octets, 0, byte_order);
	octets.remove_prefix(4);
	return result;
}

/** Read an unsigned 64-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline uint64_t read_uint64(string& octets, unsigned int byte_order = 0) {
	auto result = get_uint64(octets, 0, byte_order);
	octets.remove_prefix(8);
	return result;
}

/** Read a signed 64-bit integer from an octet string.
 * @param octets the octet string
 * @param byte_order a byte order mask
 * @throws std::out_of_range if the octet string is not long enough to
 *  fulfil the request
 * @return the integer that was read
 */
inline int64_t read_int64(string& octets, unsigned int byte_order = 0) {
	auto result = get_int64(octets, 0, byte_order);
	octets.remove_prefix(8);
	return result;
}

/** Read a given number of octets from an octet string.
 * If the octet string is not long enough to fulfil the request then all
 * available octets are returned.
 * @param octets the octet string
 * @param count the number of octets to read
 */
inline octet::string read(string& octets, string::size_type count) {
	auto result = octets.substr(0, count);
	octets.remove_prefix(result.length());
	return result;
}

/** Read a null-terminated string from an octet string.
 * @return the resulting string
 */
std::string read_cstring(string& octets);

} /* namespace holmes::octet */

#endif
