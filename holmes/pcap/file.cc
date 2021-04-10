// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/parse_error.h"
#include "holmes/pcap/file.h"

namespace holmes::pcap {

file::file(const octet::string& content):
	_content(content) {

	_magic_number = read_uint32(_content);
	if (_magic_number == 0xa1b2c3d4) {
		_byte_order = 0;
	} else if (_magic_number == 0xd4c3b2a1) {
		_byte_order = -1;
	} else {
		throw parse_error("invalid magic number in PCAP file");
	}

	_version_major = read_uint16(_content, _byte_order);
	_version_minor = read_uint16(_content, _byte_order);
	_thiszone = read_uint32(_content, _byte_order);
	_sigfigs = read_uint32(_content, _byte_order);
	_snaplen = read_uint32(_content, _byte_order);
	_network = read_uint32(_content, _byte_order);
}

record file::read() {
	return record(_content, _byte_order);
}

} /* namespace holmes::pcap */
