// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_PREFER_OLD_CONTENT
#define HOLMES_NET_TCP_PREFER_OLD_CONTENT

#include "holmes/net/tcp/reassembly_policy.h"

namespace holmes::net::tcp {

class event;

/** A reassembly policy which prefers old content over new. */
class prefer_old_content:
	public reassembly_policy {
public:
	virtual bool choose(uint64_t seq, uint64_t curseq,
		const segment* prev_old_seg, const segment* old_seg,
		const segment* next_old_seg, const segment& new_seg);
};

} /* namespace holmes::net::tcp */

#endif
