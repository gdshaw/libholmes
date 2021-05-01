// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/net/inet/checksum.h"

namespace holmes::net::inet {

void checksum::operator()(const octet::string& data) {
	// Handle complete 16-bit words.
	size_t length = data.length();
	size_t index = 0;
	while (index + 1 < length) {
		uint32_t dsum = _sum;
		dsum += get_uint16(data, index);
		_sum = dsum + (dsum >> 16);
		index += 2;
	}

	// Handle remaining byte at end, if there is one.
	if ((length & 1) != 0) {
		uint16_t octet = get_uint8(data, length - 1);
		uint32_t dsum = _sum;
		dsum += octet << 8;
		_sum = dsum + (dsum >> 16);
	}
}

} /* namespace holmes::net::inet */
