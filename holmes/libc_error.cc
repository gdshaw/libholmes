// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <cerrno>
#include <cstring>

#include <holmes/libc_error.h>

namespace holmes {

const char* libc_error_holder::strerror() const {
	// Using strerror_l because strerror is not thread safe,
	// and strerror_r defaults to a non-standard implementation
	// in glibc.
	static const locale_t locale = newlocale(0, "POSIX", 0);
	return strerror_l(_errno, locale);
}

libc_error::libc_error():
	libc_error_holder(errno),
	std::runtime_error(this->strerror()) {}

libc_error::libc_error(int errno_arg):
	libc_error_holder(errno_arg),
	std::runtime_error(this->strerror()) {}

} /* namespace holmes */
