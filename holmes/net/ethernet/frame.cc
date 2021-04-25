// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/string.h"
#include "holmes/bson/binary.h"
#include "holmes/net/ethernet/frame.h"

namespace holmes::net::ethernet {

bson::document frame::to_bson() const {
	bson::document bson_frame;
	bson_frame.append("dst_addr", bson::string(dst_addr()));
	bson_frame.append("src_addr", bson::string(src_addr()));
	bson_frame.append("ethertype", bson::int32(ethertype()));
	bson_frame.append("payload", bson::binary(payload()));
	return bson_frame;
}

} /* namespace holmes::net::ethernet */
