// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_MAXIMUM_SEGMENT_SIZE_OPTION
#define HOLMES_NET_TCP_MAXIMUM_SEGMENT_SIZE_OPTION

#include "holmes/net/tcp/option.h"

namespace holmes::net::tcp {

/** A TCP option class to represent a maximum segment size option. */
class maximum_segment_size_option:
	public option {
public:
	/** Construct TCP no operation option.
	 * @param data the raw content of the option
	 */
	maximum_segment_size_option(octet::string& data):
		option(data) {}

	virtual bson::document to_bson() const;
	virtual std::string name() const;

	/** Get the maximum segment size.
	 * @return the maximum segment size, in octets
	 */
	uint16_t maximum_segment_size() const {
		return get_uint16(data(), 2);
	}
};

} /* namespace holmes::net::tcp */

#endif
