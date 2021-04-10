// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_PCAP_RECORD
#define HOLMES_PCAP_RECORD

#include <cstdint>

#include <sys/time.h>

#include "holmes/octet/string.h"

namespace holmes::pcap {

/** A class to represent a record from within a PCAP file. */
class record {
private:
	/** The number of whole seconds in the timestamp. */
	uint32_t _ts_sec;

	/** The number of microseconds in the timestamp. */
	uint32_t _ts_usec;

	/** The captured length of this packet, in octets. */
	uint32_t _incl_len;

	/** The original length of this packet, in octets. */
	uint32_t _orig_len;

	/** The payload. */
	octet::string _payload;
public:
	/** Construct record.
	 * @param octets a source of octets
	 * @param byte_order the byte order mask
	 */
	record(octet::string& octets, unsigned int byte_order);

	/** Get the timestamp for this record.
	 * @return the timestamp
	 */
	struct timeval ts() const {
		struct timeval ts = { _ts_sec, _ts_usec };
		return ts;
	}

	/** Get the captured length of this record.
	 * @return the captured length, in octets
	 */
	uint32_t incl_len() const {
		return _incl_len;
	}

	/** Get the original length of this record.
	 * @return the original length, in octets
	 */
	uint32_t orig_len() const {
		return _orig_len;
	}

	/** Get the payload of this record.
	 * @return the payload
	 */
	const octet::string& payload() const {
		return _payload;
	}
};

} /* namespace holmes::pcap */

#endif
