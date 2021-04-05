// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_LIBC_ERROR
#define HOLMES_LIBC_ERROR

#include <stdexcept>

namespace holmes {

/** A helper class for holding the value of errno. */
class libc_error_holder {
private:
	/** The error number. */
	int _errno;
public:
	/** Construct errno holder for a specific error number.
	 * @param errno_arg the required error number
	 */
	explicit libc_error_holder(int errno_arg):
		_errno(errno_arg) {}

	/** Get the error number.
	 * @return the error number
	 */
	int errno_value() const {
		return _errno;
	}

	/** Get a string corresponding to errno.
	 * @return the string
	 */
	const char* strerror() const;
};

/** A class to represent an error corresponding to a standard C library
 * error number. */
class libc_error:
	public libc_error_holder,
	public std::runtime_error {
public:
	/** Construct standard C library error.
	 * The error message is derived automatically from the value of errno.
	 */
	libc_error();

	/** Construct standard C library error for a specific error number.
	 * @param errno_arg the required error number
	 */
	explicit libc_error(int errno_arg);
};

} /* namespace holmes */

#endif
