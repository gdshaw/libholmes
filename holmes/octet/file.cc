// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/file_buffer.h"
#include "holmes/octet/file.h"

namespace holmes::octet {

file::file(const std::string& pathname) {
	file_buffer* buffer = new file_buffer(pathname);
	string::operator=(string(*buffer, buffer->data(), buffer->length()));
}

} /* namespace holmes::octet */
