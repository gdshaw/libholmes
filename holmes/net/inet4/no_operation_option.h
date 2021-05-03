// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET4_NO_OPERATION_OPTION
#define HOLMES_NET_INET4_NO_OPERATION_OPTION

#include "holmes/net/inet4/option.h"

namespace holmes::net::inet4 {

/** An IPv4 option class to represent a no operation option. */
class no_operation_option final:
	public option {
public:
	/** Construct IPv4 no operation option.
	 * @param data the raw content of the option
	 */
	explicit no_operation_option(octet::string& data):
		option(data) {}

	std::string name() const override;
};

} /* namespace holmes::net::inet4 */

#endif
