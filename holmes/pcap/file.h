// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_PCAP_FILE
#define HOLMES_PCAP_FILE

#include <cstdint>

#include "holmes/pcap/record.h"

namespace holmes::pcap {

/** A class to represent a PCAP file. */
class file {
private:
	/** The magic number, interpreted in network byte order.
	 * This should be equal to 0xa1b2c3d4 if the file is in network byte
	 * order, or 0xd4c3b2a1 if the byte order is reversed.
	 */
	uint32_t _magic_number;

	/** The major version number. */
	uint16_t _version_major;

	/** The minor version number. */
	uint16_t _version_minor;

	/** The timezone correction, in seconds.
	 * This is the number of seconds that would need to be added to each
	 * packet timestamp in order to convert it to UTC.
	 * According to the documentation, it is always equal to zero.
	 */
	int32_t _thiszone;

	/** The number of significant figures in the timestamps.
	 * According to the documentation, this is always equal to zero.
	 */
	uint32_t _sigfigs;

	/** The maximum number of octets captured from each packet. */
	uint32_t _snaplen;

	/** The network type. */
	uint32_t _network;

	/** A byte order mask for reading the PCAP file. */
	unsigned int _byte_order;

	/** An octet string containing the remaining file content. */
	octet::string _content;
public:
	/** Construct PCAP file.
	 * @param content the file content, as an octet string
	 */
	file(const octet::string& content);

	/** Get the magic number.
	 * @return the magic number, interpreted in network byte order
	 */
	uint32_t magic_number() const {
		return _magic_number;
	}

	/** Get the major version number.
	 * @return the major version number
	 */
	uint16_t version_major() const {
		return _version_major;
	}

	/** Get the minor version number.
	 * @return the minor version number
	 */
	uint16_t version_minor() const {
		return _version_minor;
	}

	/** Get the timezone offset.
	 * This is the offset in seconds need to convert a timestamp to GMT.
	 * In practice, according to the file format specification, timestamps
	 * are always given in GMT and therefore the timezone offset is zero.
	 * @return the timezone offset, in seconds
	 */
	uint32_t thiszone() const {
		return _thiszone;
	}

	/** Get the timestamp accuracy.
	 * In practice, according to the file format specification, this field
	 * is always set to zero.
	 * @return the timestamp accuracy, as a number of significant figures
	 */
	uint32_t sigfigs() const {
		return _sigfigs;
	}

	/** Get the maximum length of captured packets.
	 * @return the maximum length, in octets
	 */
	uint32_t snaplen() const {
		return _snaplen;
	}

	/** Get the link-layer encapulation type.
	 * @return the encapsulation type, as a LINKTYPE_ constant.
	 */
	uint32_t network() const {
		return _network;
	}

	/** Check whether the end of this pcap file has been reached.
	 * @return true if at end of file, otherwise false
	 */
	bool eof() const {
		return _content.empty();
	}

	/** Read a record from this file.
	 * @return the resulting PCAP record
	 */
	record read();
};

} /* namespace holmes::pcap */

#endif
