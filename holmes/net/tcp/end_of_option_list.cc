// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/tcp/end_of_option_list.h"

namespace holmes::net::tcp {

std::string end_of_option_list::name() const {
	return std::string("EOOL");
}

} /* namespace holmes::net::tcp */
