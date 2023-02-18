// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_ADDRESS
#define HOLMES_NET_ADDRESS

#include <memory>
#include <string>
#include <iostream>

#include "holmes/octet/string.h"

namespace holmes::net {

/** A base class to represent a generic address. */
class address {
private:
	/** The raw content of this address. */
	octet::string _data;
protected:
	virtual address* _clone() const = 0;
public:
	/** Construct address from raw content.
	 * @param data the required raw content
	 */
	explicit address(const octet::string& data):
		_data(data) {}

	/** Get the raw content of this address.
	 * @return the raw content
	 */
	const octet::string& data() const {
		return _data;
	}

	/** Convert this address to a string, in canonical form.
	 * The default behaviour of this function is to delegate to
	 * this->write() using a default-constructed std::ostringstream.
	 * @return the address as a string
	 */
	virtual operator std::string() const;

	/** Write this address to a stream.
	 * The stream state is respected:
	 * - If a field width has been specified, then it applies individually
	 *   to each component of the address (but does not remain in effect
	 *   following the final component).
	 * - The case of hexademical digits follows the stream state.
	 *
	 * The output format is otherwise as close as it can be to canonical form.
	 * @param out the output stream
	 */
	virtual void write(std::ostream& out) const = 0;

	/** Clone this address.
	 * @return the cloned address
	 */
	std::unique_ptr<address> clone() const {
		return std::unique_ptr<address>(_clone());
	}
};

/** Write an IP address to an output stream.
 * The format is as described for the function inet::address::write.
 * @param out the output stream
 * @param addr the IPv4 address
 * @return the output stream
 */
inline std::ostream& operator<<(std::ostream& out, const address& addr) {
	addr.write(out);
	return out;
}

} /* namespace holmes::net */

#endif
