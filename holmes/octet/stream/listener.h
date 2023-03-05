// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_OCTET_STREAM_LISTENER
#define HOLMES_OCTET_STREAM_LISTENER

namespace holmes::octet::stream {

class event;

/** A mixin class providing the ability to listen for octet stream events. */
class listener {
public:
	virtual void handle(const event& event) = 0;
};

} /* namespace holmes::octet::stream */

#endif
