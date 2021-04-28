// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/decoder.h"

namespace holmes::net {

void decoder::handle_artefact(const std::string& protocol,
	const artefact& af) {}

void decoder::handle_ethernet(const ethernet::frame& ether_frame) {
	handle_artefact("ethernet", ether_frame);
}

void decoder::decode_ethernet(octet::string data) {
	ethernet::frame ether_frame(data);
	handle_ethernet(ether_frame);
}

} /* namespace holmes::net */
