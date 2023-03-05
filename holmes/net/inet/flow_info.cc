// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <holmes/net/inet/flow_info.h>

namespace holmes::net::inet {

flow_info& flow_info::operator|=(const flow_info& info) {
	_active |= info._active;
	_passive |= info._passive;
	return *this;
}

} /* namespace holmes::net::inet */
