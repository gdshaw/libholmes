// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/net/tcp/maximum_segment_size_option.h"

namespace holmes::net::tcp {

bson::document maximum_segment_size_option::to_bson() const {
	bson::document result = option::to_bson();
	result.append("mss", bson::int32(maximum_segment_size()));
	return result;
}

std::string maximum_segment_size_option::name() const {
	return std::string("MSS");
}

} /* namespace holmes::net::tcp */
