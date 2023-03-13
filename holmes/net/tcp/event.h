// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_EVENT
#define HOLMES_NET_TCP_EVENT

#include "holmes/octet/stream/event.h"
#include "holmes/net/tcp/segment.h"

namespace holmes::net::tcp {

/** A stream event class for events relating to a TCP connection. */
class event:
	public octet::stream::event {
private:
	/** The extended sequence number prior to this event. */
	uint64_t _from_seq;

	/** The extended sequence number following to this event. */
	uint64_t _to_seq;

	/** The segment which provided the content for this event,
	 * or null if the segment is missing. */
	const tcp::segment* _segment;
public:
	/** Construct TCP event.
	 * @param from_seq the extended sequence number prior to this event
	 * @param to_seq the extended sequence number following this event
	 * @param segment the segment which provided the content for this event
	 * @param direction true if direction of travel is client to server,
	 *  false if server to client
	 */
	event(uint64_t from_seq, uint64_t to_seq, const segment* segment,
		bool direction);

	/** Get the initial extended sequence number.
	 * @return the extended sequence number prior to this event
	 */
	uint64_t from_seq() const {
		return _from_seq;
	}

	/** Get the final extended sequence number.
	 * @return the extended sequence number following this event
	 */
	uint64_t to_seq() const {
		return _to_seq;
	}

	/** Get the segment which provided the content for this event.
	 * @return the segment, or null if there was no segment
	 */
	const tcp::segment* segment() const {
		return _segment;
	}
};

} /* namespace holmes::net::tcp */

#endif
