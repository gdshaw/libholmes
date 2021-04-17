// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_WRITER
#define HOLMES_BSON_WRITER

#include <cstddef>
#include <cstdint>

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

/* Write an unsigned 8-bit integer to a bson::writer.
 * @param bw the bson::writer to receive the data
 * @param value the value to be written
 */
void write_uint8(writer& bw, uint8_t value);

/* Write a signed 32-bit integer to a bson::writer.
 * @param bw the bson::writer to receive the data
 * @param value the value to be written
 */
void write_int32(writer& bw, int32_t value);

/** Write a signed 64-bit integer to a bson::writer.
 * @param bw the bson::writer to receive the data
 * @param value the value to be written
 */
void write_int64(writer& bw, int64_t value);

} /* namespace holmes::bson */

#endif
