// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_NET_TCP_OPTION
#define HOLMES_NET_TCP_OPTION

#include <cstdint>
#include <memory>
#include <string>

#include "holmes/octet/string.h"
#include "holmes/artefact.h"

namespace holmes::net::tcp {

/** A base class to represent a TCP option. */
class option:
	public artefact {
private:
    /** The raw content. */
    octet::string _data;
public:
	/** Construct TCP option.
	 * @param data the raw content of the option
	 */
	option(octet::string& data);

	virtual bson::document to_bson() const;

	/** Get the raw content.
	 * @return the raw content
	 */
	const octet::string& data() const {
		return _data;
	}

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

	/** Parse a TCP option.
	 * @param content the raw content
	 * @return the resulting option
	 */
	static std::unique_ptr<option> parse(octet::string& content);
};

} /* namespace holmes::net::tcp */

#endif
