// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET4_END_OF_OPTION_LIST
#define HOLMES_NET_INET4_END_OF_OPTION_LIST

#include "holmes/net/inet4/option.h"

namespace holmes::net::inet4 {

/** IPv4 option class to mark the end of the option list. */
class end_of_option_list final:
	public option {
public:
	/** Construct IPv4 end of option list.
	 * @param data the raw content of the option
	 */
	explicit end_of_option_list(octet::string& data):
		option(data) {}

	std::string name() const override;
};

} /* namespace holmes::net::inet4 */

#endif
