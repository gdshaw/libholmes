// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_WRITER
#define HOLMES_BSON_WRITER

#include <cstddef>

namespace holmes::bson {

/** A class for writing BSON data to a buffer. */
class writer {
private:
	/** A pointer to the next octet to be written. */
	unsigned char* _ptr;

	/** The number of octets remaining. */
	size_t _remaining;
public:
	/** Construct BSON writer.
	 * @param buffer the buffer to be written into
	 * @param size the size of the buffer, in octets
	 */
	writer(unsigned char* buffer, size_t size):
		_ptr(buffer),
		_remaining(size) {}

	/** Write a given number of octets.
	 * @param count the number of octets to be written
	 * @return a pointer to a buffer for receiving the octets
	 */
	unsigned char* write(size_t count);
};

} /* namespace holmes::bson */

#endif
