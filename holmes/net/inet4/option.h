// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_INET4_OPTION
#define HOLMES_NET_INET4_OPTION

#include <cstdint>
#include <memory>
#include <string>

#include "holmes/octet/string.h"
#include "holmes/artefact.h"

namespace holmes::net::inet4 {

/** A base class to represent an IPv4 option. */
class option:
	public artefact {
private:
    /** The raw content. */
    octet::string _data;
public:
	/** Construct IPv4 option.
	 * @param data a source of raw content
	 */
	explicit option(octet::string& data);

	/** Get the option type.
	 * @return the option type
	 */
	uint8_t type() const {
		return get_uint8(_data, 0);
	}

	/** Get the payload.
	 * This excludes the type and length fields.
	 */
	octet::string payload() const {
		return _data.substr(2);
	}

	/** Get the name of this option, if known.
	 * @return the name of this option
	 */
	virtual std::string name() const;

	bson::document to_bson() const override;

	/** Parse an IPv4 option.
	 * @param data a source of raw content
	 * @return the resulting option
	 */
	static std::unique_ptr<option> parse(octet::string& data);
};

} /* namespace holmes::net::inet4 */

#endif
