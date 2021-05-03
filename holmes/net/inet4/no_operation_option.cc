// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/inet4/no_operation_option.h"

namespace holmes::net::inet4 {

std::string no_operation_option::name() const {
	return std::string("NOP");
}

} /* namespace holmes::net::inet4 */
