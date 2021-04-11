// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_FILE_BUFFER
#define HOLMES_OCTET_FILE_BUFFER

#include <string>

#include "holmes/octet/buffer.h"

namespace holmes::octet {

/** A octet buffer class for holding the mmaped content of a file.
 * This class is responsible for opening and closing the file, and for
 * mapping and unmapping the content.
 */
class file_buffer final:
	public buffer {
private:
	/** The mapped file content. */
	void* _data;

	/** The number of octets mapped. */
	size_t _length;
public:
	/** Construct octet file buffer.
	 * @param pathname the pathname of the file to be mapped
	 */
	explicit file_buffer(const std::string& pathname);

	~file_buffer() override;

	unsigned char* data() override {
		return static_cast<unsigned char*>(_data);
	}

	/** Get the length of the mapped file.
	 * This is fixed at the time of construction.
	 * @return the length, in octets
	 */
	size_t length() const {
		return _length;
	}
};

} /* namespace holmes::octet */

#endif
