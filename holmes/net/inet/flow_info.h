// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_FLOW_INFO
#define HOLMES_NET_INET_FLOW_INFO

namespace holmes::net::inet {

/** A class for recording information about a flow of network traffic.
 * The main purpose of this class is to determine whether communications
 * were initiated by the source or the destination of a traffic flow.
 * It is possible for both to be true (either at different times, or less
 * commonly, as the result of an operation such as a simultaneous TCP
 * open).
 */
class flow_info {
private:
	/** True if the source is known to have initiated part or all of
	 * this flow at the transport layer.
	 * - For TCP this means observing segments with SYN=1 and ACK=0.
	 * - For UDP this means observing datagrams for which the payload
	 *   can be decoded and which corresponds to a request.
	 *
	 * If a UDP payload cannot be decoded due to lack of support for
	 * the protocol in question then this flag should not be set.
	 *
	 * In the unlikely event of a TCP simultaneous open, this flag
	 * should be set for the flows in both directions.
	 */
	bool _active = false;

	/** True if the destination is presumed to have initiated part or
	 * all of this flow at the transport layer.
	 * - For TCP this means observing segments with SYN=1 and ACK=1.
	 * - For UDP this means observing datagrams for which the payload
	 *   can be decoded and which corresponds to a response.
	 *
	 * If a UDP payload cannot be decoded due to lack of support for
	 * the protocol in question then this flag should not be set.
	 *
	 * In the unlikely event of a TCP simultaneous open, this flag
	 * should be set for the flows in both directions.
	 */
	bool _passive = false;
public:
	/** Create neutral flow information object. */
	flow_info() = default;

	/** Create flow information object with active/passive indicators.
	 * @param active true if source known to be initiator
	 * @param passive true if destination presumed to be initiator
	 */
	flow_info(bool active, bool passive):
		_active(active), _passive(passive) {}

	/** Merge this traffic flow information record with another.
	 * @param info the traffic flow information to be merged
	 * @return a reference to this
	 */
	flow_info& operator|=(const flow_info& info);

	/** Test for active source / passive destination.
	 * @return true if the source is known to have initiated part or all
	 *  of this flow, otherwise false
	 */
	bool active() const {
		return _active;
	}

	/** Test for passive source / active destination.
	 * @return true if the destination is presumed to have initiated part
	 *  or all of this flow, otherwise false
	 */
	bool passive() const {
		return _passive;
	}
};

} /* namespace holmes::net::inet */

#endif
