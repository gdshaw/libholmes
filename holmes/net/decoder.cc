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

void decoder::handle_inet6(const inet6::datagram& inet6_dgram) {
	handle_artefact("inet6", inet6_dgram);
}

void decoder::handle_icmp4(const icmp::message& icmp4_msg) {
	handle_artefact("icmp4", icmp4_msg);
}

void decoder::handle_udp(const udp::datagram& udp_dgram) {
	handle_artefact("udp", udp_dgram);
}

void decoder::handle_tcp(const tcp::segment& tcp_seg) {
	handle_artefact("tcp", tcp_seg);
}

void decoder::handle_artefact(const std::string& protocol,
	const artefact& af) {}

void decoder::decode_ethernet(octet::string data) {
	ethernet::frame ether_frame(data);
	handle_ethernet(ether_frame);
	switch (ether_frame.ethertype()) {
	case 0x0800:
		decode_inet4(ether_frame.payload());
		break;
	case 0x86dd:
		decode_inet6(ether_frame.payload());
		break;
	}
}

void decoder::decode_wrapper(
	const inet::datagram& inet_dgram, const inet::wrapper& wrapper) {

	switch (wrapper.protocol()) {
	case 1:
		if (inet_dgram.version() == 4) {
			decode_icmp4(wrapper.payload());
		}
		break;
	case 6:
		decode_tcp(inet_dgram, wrapper.payload());
		break;
	case 17:
		decode_udp(inet_dgram, wrapper.payload());
		break;
	}
}

void decoder::decode_inet4(octet::string data) {
	inet4::datagram inet4_dgram(data);
	handle_inet4(inet4_dgram);
	decode_wrapper(inet4_dgram, inet4_dgram);
}

void decoder::decode_inet6(octet::string data) {
	inet6::datagram inet6_dgram(data);
	handle_inet6(inet6_dgram);
	decode_wrapper(inet6_dgram, inet6_dgram);
}

void decoder::decode_icmp4(octet::string data) {
	auto icmp4_msg = icmp::message::parse_icmp4(data);
	handle_icmp4(*icmp4_msg);
}

void decoder::decode_udp(const inet::datagram& inet_dgram,
	octet::string data) {

	udp::datagram udp_dgram(inet_dgram, data);
	handle_udp(udp_dgram);
}

void decoder::decode_tcp(const inet::datagram& inet_dgram,
	octet::string data) {

	tcp::segment tcp_seg(inet_dgram, data);
	handle_tcp(tcp_seg);
}

} /* namespace holmes::net */
