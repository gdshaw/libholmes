// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_POLICY_LINUX_2_2
#define HOLMES_NET_TCP_POLICY_LINUX_2_2

#include "holmes/net/tcp/reassembly_policy.h"

namespace holmes::net::tcp {

/** A TCP reassembly policy to match the behaviour of Linux (>=2.2)
 * This policy is known to match:
 * - Linux 2.2.20
 * It is known to differ from:
 * - Linux 2.4.27
 */
class policy_linux_2_2:
	public reassembly_policy {
public:
	virtual bool choose(uint64_t seq, uint64_t curseq,
		const segment* prev_old_seg, const segment* old_seg,
		const segment* next_old_seg, const segment& new_seg);
};

} /* namespace holmes::net::tcp */

#endif
