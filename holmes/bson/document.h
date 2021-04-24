// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_DOCUMENT
#define HOLMES_BSON_DOCUMENT

#include <vector>
#include <string>

#include "holmes/bson/value.h"
#include "holmes/bson/any.h"

namespace holmes::bson {

/** A BSON class to represent a document. */
class document:
	public value {
public:
	/** The key type for this document. */
	typedef std::string key_type;

	/** The type to which keys are mapped by this document. */
	typedef bson::any mapped_type;

	/** The type of members of this document. */
	typedef std::pair<key_type, mapped_type> value_type;
private:
	/** The members of this document. */
	std::vector<value_type> _members;
public:
	/** Construct empty BSON document. */
	document() = default;

	/** Decode from an octet string.
	 * @param bd the BSON data to be decoded
	 * @param dec a flag to trigger decoding
	 */
	document(octet::string& bd, const decode& dec);

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	any& at(const std::string& name) override;
	const any& at(const std::string& name) const override;

	/** Append a member to this document.
	 * @param name the name of the member
	 * @param value the value of the member
	 */
	void append(const std::string& name, const bson::value& value);
};

} /* namespace holmes::bson */

#endif
