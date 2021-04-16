// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/writer.h"

namespace holmes::bson {

unsigned char* writer::write(size_t count) {
	if (_remaining < count) {
		throw std::out_of_range("BSON buffer full");
	}
	auto buffer = _ptr;
	_ptr += count;
	_remaining -= count;
	return buffer;
}

} /* namespace holmes::bson */
