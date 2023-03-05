#// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <sstream>

#include "holmes/bson/int32.h"
#include "holmes/bson/string.h"
#include "holmes/bson/document.h"
#include "holmes/net/inet/five_tuple.h"

namespace holmes::net::inet {

five_tuple::five_tuple(uint8_t protocol, inet::address& dst_addr,
	uint16_t dst_port, inet::address& src_addr, uint16_t src_port):
	_protocol(protocol),
	_dst_addr(dst_addr.clone()),
	_dst_port(dst_port),
	_src_addr(src_addr.clone()),
	_src_port(src_port) {}

five_tuple::five_tuple(const inet::datagram& inet_dgram,
	const inet::l4_packet& l4_pkt):
	_protocol(inet_dgram.protocol()),
	_dst_addr(inet_dgram.dst_addr().clone()),
	_dst_port(l4_pkt.dst_port()),
	_src_addr(inet_dgram.src_addr().clone()),
	_src_port(l4_pkt.src_port()) {}

five_tuple::operator std::string() const {
	std::stringstream out;
	out << int(protocol()) << ";"
		<< src_addr() << ":" << src_port() << "=>"
		<< dst_addr() << ":" << dst_port();
	return out.str();
}

bson::document five_tuple::to_bson() const {
	bson::document bson_five_tuple;
	bson_five_tuple.append("protocol", bson::int32(protocol()));
	bson_five_tuple.append("dst_addr", bson::string(dst_addr()));
	bson_five_tuple.append("dst_port", bson::int32(dst_port()));
	bson_five_tuple.append("src_addr", bson::string(src_addr()));
	bson_five_tuple.append("src_port", bson::int32(src_port()));
	return bson_five_tuple;
}

bool operator==(const five_tuple& lhs, const five_tuple& rhs) {
	if (lhs.protocol() != rhs.protocol()) {
		return false;
	}
	if (lhs.dst_addr() != rhs.dst_addr()) {
		return false;
	}
	if (lhs.dst_port() != rhs.dst_port()) {
		return false;
	}
	if (lhs.src_addr() != rhs.src_addr()) {
		return false;
	}
	if (lhs.src_port() != rhs.src_port()) {
		return false;
	}
	return true;
}

std::strong_ordering operator<=>(const five_tuple& lhs, const five_tuple& rhs) {
	if (lhs.protocol() != rhs.protocol()) {
		return lhs.protocol() <=> rhs.protocol();
	}
	if (lhs.dst_addr() != rhs.dst_addr()) {
		return lhs.dst_addr() <=> rhs.dst_addr();
	}
	if (lhs.dst_port() != rhs.dst_port()) {
		return lhs.dst_port() <=> rhs.dst_port();
	}
	if (lhs.src_addr() != rhs.src_addr()) {
		return lhs.src_addr() <=> rhs.src_addr();
	}
	return lhs.src_port() <=> rhs.src_port();
}

} /* namespace holmes::net::inet */
