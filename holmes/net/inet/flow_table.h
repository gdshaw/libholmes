// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_FLOW_TABLE
#define HOLMES_NET_INET_FLOW_TABLE

#include <map>
#include <set>
#include <iostream>

#include "holmes/net/inet/five_tuple.h"
#include "holmes/net/inet/flow_info.h"

namespace holmes::net::inet {

/** A class for recording information about network traffic flows. */
class flow_table {
private:
	/** The flows in this table. */
	std::map<five_tuple, flow_info> _flows;
public:
	/** Ingest a TCP segment.
	 * @param dgram the IP datagram containing the segment
	 * @param seg the segment to be ingested
	 */
	void ingest(const inet::datagram& dgram, const tcp::segment& seg);

	/** Summarise the network traffic flows in this table.
	 * When summarised:
	 * - Only outbound flows from the active endpoint are reported.
	 * - The source port number is disregarded.
	 */
	std::set<five_tuple> summarise() const;

	/** Dump the content of this table to an output stream.
	 * @param out the output stream to be written to
	 */
	void dump(std::ostream& out);
};

} /* namespace holmes::net::inet */

#endif
