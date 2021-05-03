// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/inet4/end_of_option_list.h"

namespace holmes::net::inet4 {

std::string end_of_option_list::name() const {
	// tcpdump uses EOL, but the official name is EOOL.
	return std::string("EOOL");
}

} /* namespace holmes::net::inet4 */
