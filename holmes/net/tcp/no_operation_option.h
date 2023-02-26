// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_NO_OPERATION_OPTION
#define HOLMES_NET_TCP_NO_OPERATION_OPTION

#include "holmes/net/tcp/option.h"

namespace holmes::net::tcp {

/** A TCP option class to represent a no operation option. */
class no_operation_option:
	public option {
public:
	/** Construct TCP no operation option.
	 * @param data the raw content of the option
	 */
	no_operation_option(octet::string& data):
		option(data) {}

	virtual std::string name() const;
};

} /* namespace holmes::net::tcp */

#endif
