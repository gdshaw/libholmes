// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/pcap/record.h"

namespace holmes::pcap {

record::record(octet::string& octets, unsigned int byte_order):
	_ts_sec(read_uint32(octets, byte_order)),
	_ts_usec(read_uint32(octets, byte_order)),
	_incl_len(read_uint32(octets, byte_order)),
	_orig_len(read_uint32(octets, byte_order)),
	_payload(read(octets, _incl_len)) {}

} /* namespace holmes::pcap */
