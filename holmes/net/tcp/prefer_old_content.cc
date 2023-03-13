// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/tcp/prefer_old_content.h"

namespace holmes::net::tcp {

bool prefer_old_content::choose(uint64_t seq, uint64_t curseq,
	const segment* prev_old_seg, const segment* old_seg,
	const segment* next_old_seg, const segment& new_seg) {

	// If there is no conflict then accept the new content.
	// Otherwise, prefer the old content.
	return !old_seg;
}

} /* namespace holmes::net::tcp */
