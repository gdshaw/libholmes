// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "holmes/libc_error.h"
#include "holmes/octet/file_buffer.h"

namespace holmes::octet {

file_buffer::file_buffer(const std::string& pathname) {
	// Open the file.
	int fd = open(pathname.c_str(), O_RDONLY);
	if (fd == -1) {
		throw libc_error();
	}

	// Determine the length of the file.
	struct stat sb;
	if (fstat(fd, &sb) == -1) {
		close(fd);
		throw libc_error();
	}
	if (sb.st_size < 0) {
		// This condition should not be possible for regular files, but
		// does not appear to be forbidden in the general case, so check
		// before casting the length to an unsigned type.
		close(fd);
		throw libc_error(EINVAL);
	}
	_length = sb.st_size;

	// Map the content of the file into memory.
	_data = mmap(0, _length, PROT_READ, MAP_PRIVATE, fd, 0);
	if (_data == MAP_FAILED) {
		close(fd);
		throw libc_error();
	}

	// Close the file.
	close(fd);
}

file_buffer::~file_buffer() {
	munmap(_data, _length);
}

} /* namespace holmes::octet */
