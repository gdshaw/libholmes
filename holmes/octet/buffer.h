// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_BUFFER
#define HOLMES_OCTET_BUFFER

#include <cstdlib>
#include <atomic>

namespace holmes::octet {

/** An abstract base class for holding the shared content of an octet string.
 * Instances of this class are reference-counted, starting from an initial
 * count of one. The count can be changed only through the link and unlink
 * member functions. Instances are deleted if and when the count reaches
 * zero, therefore they must either be heap-allocated using operator new,
 * or used in a manner such that the count can never reach zero.
 *
 * Every octet string must refer to an instance of this class. If an octet
 * string utilises content from another octet string without copying, then
 * they must refer to the same instance of this class (with the reference
 * count adjusted accordingly).
 */
class buffer {
private:
	/** The number of references to this buffer.
	 * The buffer should be deleted if the reference count reaches zero.
	 */
	std::atomic_size_t _refcount = 1;
public:
	buffer() = default;
	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

	/** Destroy octet buffer.
	 * If any special action is required to dispose of shared content once
	 * there are no more references to it, then this destructor must be
	 * overridden to perform that action.
	 */
	virtual ~buffer() = default;

	/** Get buffer content.
	 * @return a pointer to the buffer content.
	 */
	virtual unsigned char* data() = 0;

	/** Make new link to buffer object.
	 * This function causes the reference count to be incremented.
	 * @param buf the buffer to be linked
	 * @return a pointer to the linked buffer
	 */
	static buffer* link(buffer& buf) {
		++buf._refcount;
		return &buf;
	}

	/** Release link to buffer object.
	 * This function causes the reference count to be decremented,
	 * and the buffer deleted if the count reaches zero.
	 * @param buf the buffer to be unlinked
	 */
	static void unlink(buffer& buf) {
		if (!--buf._refcount) {
			delete &buf;
		}
	}
};

} /* namespace holmes::octet */

#endif
