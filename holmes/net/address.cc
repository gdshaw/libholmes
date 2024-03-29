// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <sstream>

#include "holmes/net/address.h"

namespace holmes::net {

address::operator std::string() const {
	std::ostringstream out;
	_write(out);
	return out.str();
}

} /* namespace holmes::net */
