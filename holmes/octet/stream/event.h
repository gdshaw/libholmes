// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_STREAM_EVENT
#define HOLMES_OCTET_STREAM_EVENT

#include "holmes/octet/string.h"

namespace holmes::octet::stream {

/** A base class to represent a fragment of a reconstructed octet stream.
 * This base class provides access to generic properties of the event which
 * are not specific to any particular transport protocol:
 *
 * - the direction of travel
 * - an optional in-band payload
 *
 * Subclasses may augment this with information that is specific to
 * particular types of connection, for example the segment from which the
 * payload was extracted in the case of a TCP connection.
 */
class event {
private:
	/** The in-band payload associated with this event.
	 * This should be empty if there is no in-band payload.
	 */
	string _payload;

	/** The direction of travel.
	 * This is true for client to server, false for server to client.
	 */
	bool _direction;
public:
	/** Construct event.
	 * @param payload the in-band payload, if any
	 * @param direction true if direction of travel is client to server,
	 *  false if server to client
	 * @param gap true if there is a gap, otherwise false
	 */
	event(const string& payload, bool direction):
		_payload(payload),
		_direction(direction) {}

	virtual ~event() = default;
	event(const event&) = default;
	event(event&&) = default;
	event& operator=(const event&) = default;
	event& operator=(event&&) = default;

	/** Get the payload.
	 * @return the payload, or an empty octet string if none
	 */
	const string& payload() const {
		return _payload;
	}

	/** Get the direction of travel to which this event refers.
	 * @return true if client to server, false if server to client
	 */
	bool direction() const {
		return _direction;
	}
};

} /* namespace holmes::octet::stream */

#endif
