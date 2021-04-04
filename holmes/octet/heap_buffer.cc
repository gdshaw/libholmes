// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/heap_buffer.h"

namespace holmes::octet {

unsigned char* heap_buffer::data() {
	return reinterpret_cast<unsigned char*>(this) + sizeof(*this);
}

} /* namespace holmes::octet */
