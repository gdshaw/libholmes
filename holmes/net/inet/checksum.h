// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET_CHECKSUM
#define HOLMES_NET_INET_CHECKSUM

#include "holmes/octet/string.h"

namespace holmes::net::inet {

/** A class to represent an Internet Protocol checksum.
 * This checksum algorithm is used by several internet-related protocols
 * including IPv4, UDP, TCP and ICMP.
 *
 * The checksum is defined in RFC 791 to be the ones-complement of the
 * ones-complement sum of the 16-bit words to be checksummed. A more
 * detailed description can be found in RFC 1071.
 *
 * The implementation provided by this class does not limit the number
 * of words which can be incorporated into the checksum.
 */
class checksum {
private:
	/** The accumulated checksum.
	 * This must be inverted before use.
	 */
	uint16_t _sum = 0;
public:
	/** Get the resulting checksum.
	 * @return the resulting checksum
	 */
	operator uint16_t() const {
		return ~_sum;
	}

	/** Incorporate a 16-bit word into the checksum.
	 * @param word the 16-bit word to be incorporated
	 */
	void operator()(uint16_t word) {
		uint32_t dsum = _sum;
		dsum += word;
		_sum = dsum + (dsum >> 16);
	}

	/** Incorporate a sequence of octets into the checksum.
	 * If the sequence contains an odd number of octets then it is padded
	 * with a zero for incorporation into the checksum. Be aware therefore
	 * that incorporating sequences separately does not necessarily have
	 * the same effect as incorporating a concatenated sequence.
	 * @param data the octets to be incorporated
	 */
	void operator()(const octet::string& data);
};

} /* namespace holmes::net::inet */

#endif
