// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/tcp/segment.h"
#include "holmes/net/tcp/policy_linux_2_2.h"

namespace holmes::net::tcp {

bool policy_linux_2_2::choose(uint64_t seq, uint64_t curseq,
	const segment* prev_old_seg, const segment* old_seg,
	const segment* next_old_seg, const segment& new_seg) {

	// If there is no old segment then accept the new segment.
	if (!old_seg) {
		return true;
	}

	// If the new segment starts at a lower sequence number than the old
	// segment then accept the new segment.
	if (new_seg.seq(seq) < old_seg->seq(seq)) {
		return true;
	}

	// If the old and new segments start at the same sequence number,
	// but the new segment is the same length or longer than the old
	// segment, then accept the new segment.
	if (new_seg.seq(seq) == old_seg->seq(seq)) {
		if (new_seg.nextseq(seq) >= old_seg->nextseq(seq)) {
			return true;
		}
	}

	// In all other cases, retain the old segment.
	return false;
}

} /* namespace holmes::net::tcp */
