// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_END_OF_OPTION_LIST
#define HOLMES_NET_TCP_END_OF_OPTION_LIST

#include "holmes/net/tcp/option.h"

namespace holmes::net::tcp {

/** TCP option class to mark the end of the option list. */
class end_of_option_list:
	public option {
public:
	/** Construct TCP end of option list.
	 * @param data the raw content of the option
	 */
	end_of_option_list(octet::string& data):
		option(data) {}

	virtual std::string name() const;
};

} /* namespace holmes::net::tcp */

#endif
