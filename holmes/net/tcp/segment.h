// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_SEGMENT
#define HOLMES_NET_TCP_SEGMENT

#include <memory>
#include <vector>

#include "holmes/octet/string.h"
#include "holmes/net/inet/datagram.h"
#include "holmes/net/inet/l4_packet.h"
#include "holmes/net/tcp/option.h"

namespace holmes::net::tcp {

/** A class to represent a TCP segment. */
class segment:
	public inet::l4_packet {
public:
        /** The internet protocol number. */
        static const uint8_t protocol = 6;
private:
	/** A type to represent a list of options. */
	typedef std::vector<std::unique_ptr<option>> option_list;

	/** The pseudo-header checksum. */
	inet::checksum _phc;

	/** The raw content. */
	octet::string _data;

	/** The list of options. */
	mutable std::unique_ptr<option_list> _options;

	/** Make the list of options.
	 * @return the newly-created list of options
	 */
	std::unique_ptr<option_list> _make_options() const;
public:
	/** Construct TCP segment.
	 * @param inet_datagram the IP datagram to which this belongs.
	 * @param data the raw content of the segment
	 */
	segment(const inet::datagram& inet_datagram, octet::string& data);

	/** Copy-construct TCP segment.
	 * @param that the segment to be copied
	 */
	segment(const segment& that):
		_phc(that._phc),
		_data(that._data) {}

	/** Copy-assign TCP segment.
	 * @param that the segment to be copied
	 */
	segment& operator=(const segment& that) {
		if (this != &that) {
			this->_phc = that._phc;
			this->_data = that._data;
			this->_options.reset();
		}
		return *this;
	}

	bson::document to_bson() const override;

	/** Get the source port.
	 * @return the source port
	 */
	uint16_t src_port() const override {
		return get_uint16(_data, 0);
	}

	/** Get the destination port.
	 * @return the destination port
	 */
	uint16_t dst_port() const override {
		return get_uint16(_data, 2);
	}

	/** Get the wrapped sequence number.
	 * @return the wrapped sequence number
	 */
	uint32_t seq() const {
		return get_uint32(_data, 4);
	}

	/** Get the wrapped acknowledgement number.
	 * @return the wrapped acknowledgement number
	 */
	uint32_t ack() const {
		return get_uint32(_data, 8);
	}

	/** Get the extended sequence number.
	 * @param ref the sequence number to use as a reference
	 * @return the extended sequence number
	 */
	uint64_t seq(uint64_t ref) const {
		uint32_t diff = seq() - ref + 0x80000000;
		return ref + diff - 0x80000000;
	}

	/** Get the extended acknowledgement number.
	 * @param ref the sequence number to use as a reference
	 * @return the extended acknowledgement number
	 */
	uint64_t ack(uint64_t ref) const {
		uint32_t diff = ack() - ref + 0x80000000;
		return ref + diff - 0x80000000;
	}

	/** Get the following extended sequence number.
	 * This is the first extended sequence number which lies beyond the end
	 * of this segment.
	 * @param ref the sequence number to use as a reference
	 * @return the following extended sequence number
	 */
	uint64_t nextseq(uint64_t ref) const {
		return seq(ref) + payload().length() +
			(syn_flag() ? 1 : 0) +
			(fin_flag() ? 1 : 0);
	}

	/** Get the data offset.
	 * @return the data offset, in 32-bit words
	 */
	unsigned int data_offset() const {
		return (_data[12] >> 4) & 0xf;
	}

	/** Get the flags.
	 * This includes the reserved bits, but not the data offset field.
	 * @return the flags
	 */
	bool flags() const {
		return get_uint16(_data, 12) & 0xfff;
	}

	/** Get the NS flag.
	 * @return the NS flag
	 */
	bool ns_flag() const {
		return _data[12] & 0x01;
	}

	/** Get the CWR flag.
	 * @return the CWR flag
	 */
	bool cwr_flag() const {
		return _data[13] & 0x80;
	}

	/** Get the ECE flag.
	 * @return the ECE flag
	 */
	bool ece_flag() const {
		return _data[13] & 0x40;
	}

	/** Get the URG flag.
	 * @return the URG flag
	 */
	bool urg_flag() const {
		return _data[13] & 0x20;
	}

	/** Get the ACK flag.
	 * @return the ACK flag
	 */
	bool ack_flag() const {
		return _data[13] & 0x10;
	}

	/** Get the PSH flag.
	 * @return the PSH flag
	 */
	bool psh_flag() const {
		return _data[13] & 0x08;
	}

	/** Get the RST flag.
	 * @return the RST flag
	 */
	bool rst_flag() const {
		return _data[13] & 0x04;
	}

	/** Get the SYN flag.
	 * @return the SYN flag
	 */
	bool syn_flag() const {
		return _data[13] & 0x02;
	}

	/** Get the FIN flag.
	 * @return the FIN flag
	 */
	bool fin_flag() const {
		return _data[13] & 0x01;
	}

	/** Get the window size.
	 * By default this is measured in octets, however an optional scaling
	 * factor may be applicable.
	 * @return the window size
	 */
	uint16_t window_size() const {
		return get_uint16(_data, 14);
	}

	/** Get the recorded checksum.
	 * @return the checksum
	 */
	uint16_t recorded_checksum() const {
		return get_uint16(_data, 16);
	}

	/** Get the calculated checksum.
	 * This is the checksum as calculated by summing every word in the
	 * IP pseudo-header, plus every word in the TCP header except for the
	 * checksum field, plus every word in the payload (padded with a zero
	 * octet if necessary to make a whole number of words).
	 * @return the calculated checksum
	 */
	uint16_t calculated_checksum() const;

	/** Get the urgent pointer.
	 * @return the urgent pointer
	 */
	uint16_t urgent_pointer() const {
		return get_uint16(_data, 18);
	}

	/** Get the list of options.
	 * @return the list of options
	 */
	const option_list& options() const {
		if (!_options) {
			_options = _make_options();
		}
		return *_options;
	}

	/** Get the payload.
	 * @return the payload
	 */
	octet::string payload() const {
		return _data.substr(data_offset() * 4);
	}

	/** Test whether this segment contains a given extended sequence number.
	 * @param ref the extended sequence number to test
	 * @return true if contained within this segment, otherwise false
	 */
	bool contains(uint64_t ref) const {
		uint64_t extseq = seq(ref);
		return (ref >= extseq) && (ref < extseq + payload().length());
	}
};

} /* namespace holmes::net::tcp */

#endif
