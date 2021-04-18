// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/value.h"

namespace holmes::bson {

bool value::is_null() const {
	return false;
}

} /* namespace holmes::bson */
