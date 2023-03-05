// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_REASSEMBLY_POLICY
#define HOLMES_NET_TCP_REASSEMBLY_POLICY

#include <cstdint>

namespace holmes::net::tcp {

class segment;

/** An abstract base class to specify policy for reassembling a TCP stream.
 * Subclasses are permitted to be stateful, in which case they may assume
 * that:
 * - New segments are presented in time order.
 * - For each new segment, regions of overlap are considered in ascending
 *   order of the extended sequence number.
 */
class reassembly_policy {
public:
	virtual ~reassembly_policy() = default;

	/** Choose between old and new segments.
	 * @param seq the extended sequence number at which the proposed
	 *  replacement would begin
	 * @param curseq the current extended sequence number, up to which
	 *  content has already been delivered
	 * @param prev_old_seg the segment preceding the existing segment,
	 *  or null if none
	 * @param old_seg the existing segment, or null if none
	 * @param next_old_seg the segment following the existing segment,
	 *  or null if none
	 * @param new_seg the potential replacement
	 * @return true to replace existing segment, otherwise false
	 */
	virtual bool choose(uint64_t seq, uint64_t curseq,
		const segment* prev_old_seg, const segment* old_seg,
		const segment* next_old_seg, const segment& new_seg) = 0;
};

} /* namespace holmes::net::tcp */

#endif
