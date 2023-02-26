// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/int32.h"
#include "holmes/bson/binary.h"
#include "holmes/net/icmp/echo/message.h"

namespace holmes::net::icmp::echo {

bson::document message::to_bson() const {
	bson::document bson_message(icmp::message::to_bson());
	bson_message.append("id", bson::int32(id()));
	bson_message.append("seqnum", bson::int32(seqnum()));
	bson_message.append("payload", bson::binary(payload()));
	return bson_message;
}

} /* namespace holmes::net::icmp::echo */
