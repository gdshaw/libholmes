// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/boolean.h"
#include "holmes/bson/int32.h"
#include "holmes/bson/int64.h"
#include "holmes/bson/binary.h"
#include "holmes/net/inet/checksum.h"
#include "holmes/net/tcp/segment.h"

namespace holmes::net::tcp {

using namespace bson;

segment::segment(const inet::datagram& inet_datagram, octet::string& data):
        _phc(inet_datagram.make_pseudo_header_checksum(protocol, data.length())),
	_data(data) {}

bson::document segment::to_bson() const {
	bson::document bson_checksum;
	bson_checksum.append("recorded", bson::int32(recorded_checksum()));
	bson_checksum.append("calculated", bson::int32(calculated_checksum()));

	bson::document bson_dgram;
	bson_dgram.append("src_port", bson::int32(src_port()));
	bson_dgram.append("dst_port", bson::int32(dst_port()));
	bson_dgram.append("seq", bson::int64(seq()));
	bson_dgram.append("ack", bson::int64(ack()));
	bson_dgram.append("flags", bson::int32(flags()));
	bson_dgram.append("ns_flag", bson::boolean(ns_flag()));
	bson_dgram.append("cwr_flag", bson::boolean(cwr_flag()));
	bson_dgram.append("ece_flag", bson::boolean(ece_flag()));
	bson_dgram.append("urg_flag", bson::boolean(urg_flag()));
	bson_dgram.append("ack_flag", bson::boolean(ack_flag()));
	bson_dgram.append("psh_flag", bson::boolean(psh_flag()));
	bson_dgram.append("rst_flag", bson::boolean(rst_flag()));
	bson_dgram.append("syn_flag", bson::boolean(syn_flag()));
	bson_dgram.append("fin_flag", bson::boolean(fin_flag()));
	bson_dgram.append("window_size", bson::int32(window_size()));
	bson_dgram.append("checksum", bson_checksum);
	bson_dgram.append("urgent_pointer", bson::int32(urgent_pointer()));
	bson_dgram.append("payload", bson::binary(payload()));
	return bson_dgram;
}

uint16_t segment::calculated_checksum() const {
	inet::checksum checksum = _phc;
	checksum(_data.substr(0, 16));
	checksum(_data.substr(18));
	return checksum;
}

} /* namespace holmes::net::tcp */
