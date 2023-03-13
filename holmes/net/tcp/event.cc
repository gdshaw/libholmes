// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/tcp/event.h"

namespace holmes::net::tcp {

octet::string extract_payload(uint64_t from_seq, uint64_t to_seq,
	const tcp::segment* segment) {

	octet::string payload;
	if (segment) {
		uint32_t offset = from_seq - segment->seq();
		uint32_t length = to_seq - from_seq;
		payload = segment->payload().substr(offset, length);
	}
	return payload;
}

event::event(uint64_t from_seq, uint64_t to_seq, const tcp::segment* segment,
	bool direction):
	octet::stream::event(
		extract_payload(from_seq, to_seq, segment), direction),
	_from_seq(from_seq),
	_to_seq(to_seq),
	_segment(segment) {}

} /* namespace holmes::net::tcp */
