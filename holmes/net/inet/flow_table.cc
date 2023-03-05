// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/inet/datagram.h"
#include "holmes/net/tcp/segment.h"
#include "holmes/net/inet/flow_table.h"

namespace holmes::net::inet {

void flow_table::ingest(const inet::datagram& dgram,
	const tcp::segment& seg) {

	five_tuple key(dgram, seg);
	bool active = seg.syn_flag() && !seg.ack_flag();
	bool passive = seg.syn_flag() && seg.ack_flag();
	_flows[key] |= flow_info(active, passive);
}

std::set<five_tuple> flow_table::summarise() const {
	std::set<five_tuple> summary;
	for (const auto& i : _flows) {
		std::unique_ptr<inet::address> src_addr = i.first.src_addr().clone();
		uint16_t src_port = i.first.src_port();
		std::unique_ptr<inet::address> dst_addr = i.first.dst_addr().clone();
		uint16_t dst_port = i.first.dst_port();
		uint8_t protocol = i.first.protocol();
		if (!i.second.active()) {
			if (i.second.passive()) {
				std::swap(src_addr, dst_addr);
				std::swap(src_port, dst_port);
			} else {
				continue;
			}
		}
		five_tuple key(protocol, *src_addr, 0, *dst_addr, dst_port);
		summary.insert(key);
	}
	return summary;
}

void flow_table::dump(std::ostream& out) {
	for (const auto& i : _flows) {
		out << i.first << std::endl;
	}
}

} /* namespace holmes::net::inet */
