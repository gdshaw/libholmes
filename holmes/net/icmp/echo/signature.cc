// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/octet/pattern/any.h"
#include "holmes/net/icmp/echo/signature.h"

namespace holmes::net::icmp::echo {

signature::signature(const bson::document& bson_sig) {
	try {
		int64_t id = bson_sig.at("id");
		_id = id;
	} catch (std::out_of_range&) {
		// No action: optional field
	}
	try {
		int64_t seqnum = bson_sig.at("seqnum");
		_seqnum = seqnum;
	} catch (std::out_of_range&) {
		// No action: optional field
	}
	try {
		_payload = octet::pattern::any(bson_sig.at("payload"));
	} catch (std::out_of_range&) {
		// No action: optional field
	}
}

bool signature::operator()(const icmp::echo::message& msg) const {
	if (_id) {
		if (msg.id() != *_id) {
			return false;
		}
	}
	if (_seqnum) {
		if (msg.seqnum() != *_seqnum) {
			return false;
		}
	}
	if (_payload) {
		octet::string payload = msg.payload();
		if (!(*_payload)(payload)) {
			return false;
		}
		if (!payload.empty()) {
			return false;
		}
	}
	return true;
}

} /* namespace holmes::net::icmp::echo */
