// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_DECODER
#define HOLMES_NET_DECODER

#include <string>

#include "holmes/artefact.h"
#include "holmes/net/ethernet/frame.h"

namespace holmes::net {

/** A base class for deeply decoding network packets.
 * Given a network packet of a supported type, instances of this class will
 * first decode the outermost protocol layer, then do likewise for any
 * payload or payloads found inside it.
 *
 * This base class contains the decoding mechanism, and provides a number
 * of virtual handler functions which are invoked when particular types of
 * network packet have been decoded. There is also a generic handler
 * function, which can be invoked for any type of network packet.
 *
 * The default behaviour is for the specific handlers to invoke the generic
 * handler, and for the generic handler to do nothing. It is intended that
 * one or more of the handler functions should be overridden in a subclass,
 * in order to act on the decoded network packets as desired.
 *
 * Network packets are decoded in isolation of each other, therefore there
 * is no provision within this class to perform fragment or stream
 * reassembly.
 */
class decoder {
protected:
	/** Handle any type of decoded artefact.
	 * If not overridden then this handler does nothing.
	 * @param proto the name of the network protocol
	 * @param af the artefact to be handled
	 */
	virtual void handle_artefact(const std::string& proto, const artefact& af);

	/** Handle a decoded Ethernet frame.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param ether_frame the Ethernet frame to be handled
	 */
	virtual void handle_ethernet(const ethernet::frame& ether_frame);
public:
	/** Decode an Ethernet frame.
	 * @param raw the raw data to be decoded
	 */
	void decode_ethernet(octet::string data);
};

} /* namespace holmes::net */

#endif
