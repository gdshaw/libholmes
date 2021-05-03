// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/decoder.h"

namespace holmes::net {

void decoder::handle_ethernet(const ethernet::frame& ether_frame) {
	handle_artefact("ethernet", ether_frame);
}

void decoder::handle_inet4(const inet4::datagram& inet4_dgram) {
	handle_artefact("inet4", inet4_dgram);
}

void decoder::handle_icmp4(const icmp::message& icmp4_msg) {
	handle_artefact("icmp4", icmp4_msg);
}

void decoder::handle_artefact(const std::string& protocol,
	const artefact& af) {}

void decoder::decode_ethernet(octet::string data) {
	ethernet::frame ether_frame(data);
	handle_ethernet(ether_frame);
	if (ether_frame.ethertype() == 0x0800) {
		decode_inet4(ether_frame.payload());
	}
}

void decoder::decode_inet4(octet::string data) {
	inet4::datagram inet4_dgram(data);
	handle_inet4(inet4_dgram);
	if (inet4_dgram.protocol() == 1) {
		decode_icmp4(inet4_dgram.payload());
	}
}

void decoder::decode_icmp4(octet::string data) {
	icmp::message icmp4_msg(data);
	handle_icmp4(icmp4_msg);
}

} /* namespace holmes::net */
