// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_HEAP_BUFFER
#define HOLMES_OCTET_HEAP_BUFFER

#include <stdexcept>

#include "holmes/octet/buffer.h"

namespace holmes::octet {

/** A class for holding the shared content of an octet string on the heap.
 * The content is co-allocated with the buffer object within a single heap
 * block. Custom new and delete operators are provided for allocating a
 * buffers with the required capacity.
 */
class heap_buffer final:
	public buffer {
public:
	unsigned char* data() override;

	/** Allocate heap buffer.
	 * @param instance_size the size of the heap_buffer instance to be
	 *  constructed, in octets, excluding any co-allocated data
	 * @param capacity the required buffer capacity, in octets
	 */
	void* operator new(size_t instance_size, size_t capacity) {
		if (void* p = malloc(instance_size + capacity)) {
			return p;
		} else {
			throw std::bad_alloc();
		}
	}

	/** Deallocate heap buffer.
	 * This will have the effect of deallocating both the header object and
	 * any co-allocated data.
	 * @param buf the buffer object to deallocate
	 */
	void operator delete(void* buf) {
		free(buf);
	}
};

} /* namespace holmes::octet */

#endif
