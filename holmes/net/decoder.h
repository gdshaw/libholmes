// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_DECODER
#define HOLMES_NET_DECODER

#include <string>

#include "holmes/artefact.h"
#include "holmes/net/ethernet/frame.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet/wrapper.h"
#include "holmes/net/inet4/datagram.h"
#include "holmes/net/inet6/datagram.h"
#include "holmes/net/icmp/message.h"
#include "holmes/net/udp/datagram.h"
#include "holmes/net/tcp/segment.h"

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
	/** Handle a decoded Ethernet frame.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param ether_frame the Ethernet frame to be handled
	 */
	virtual void handle_ethernet(const ethernet::frame& ether_frame);

	/** Handle a decoded IPv4 datagram.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param inet4_dgram the datagram to be handled
	 */
	virtual void handle_inet4(const inet4::datagram& inet4_dgram);

	/** Handle a decoded IPv6 datagram.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param inet6_dgram the datagram to be handled
	 */
	virtual void handle_inet6(const inet6::datagram& inet6_dgram);

	/** Handle a decoded ICMPv4 message.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param icmp4_msg the message to be handled
	 */
	virtual void handle_icmp4(const icmp::message& icmp4_msg);

	/** Handle a decoded UDP datagram.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param udp_dgram the datagram to be handled
	 */
	virtual void handle_udp(const udp::datagram& udp_dgram);

	/** Handle a decoded TCP segment.
	 * If not overridden then this handler forwards to decoder::handle_artefact.
	 * @param tcp_seg the segment to be handled
	 */
	virtual void handle_tcp(const tcp::segment& tcp_seg);

	/** Handle any type of decoded artefact.
	 * If not overridden then this handler does nothing.
	 * @param proto the name of the network protocol
	 * @param af the artefact to be handled
	 */
	virtual void handle_artefact(const std::string& proto, const artefact& af);
public:
	/** Decode an Ethernet frame.
	 * @param raw the raw data to be decoded
	 */
	void decode_ethernet(octet::string data);

	/** Decode an IPv4 datagram.
	 * @param raw the raw data to be decoded
	 */
	void decode_inet4(octet::string data);

	/** Decode an IPv6 datagram.
	 * @param raw the raw data to be decoded
	 */
	void decode_inet6(octet::string data);

	/** Decode an IP transport-layer protocol.
	 * @param inet_dgram the containing IP datagram
	 * @param wrapper the wrapper for the transport protocol
	 */
	void decode_wrapper(const inet::datagram& inet_dgram,
		const inet::wrapper& wrapper);

	/** Decode an ICMPv4 datagram.
	 * @param raw the raw data to be decoded
	 */
	void decode_icmp4(octet::string data);

	/** Decode a UDP datagram.
	 * @param raw the raw data to be decoded
	 */
	void decode_udp(const inet::datagram& inet_dgram,
		octet::string data);

	/** Decode a TCP segment.
	 * @param raw the raw data to be decoded
	 */
	void decode_tcp(const inet::datagram& inet_dgram,
		octet::string data);
};

} /* namespace holmes::net */

#endif
