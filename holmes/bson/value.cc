// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <stdexcept>

#include "holmes/bson/value.h"

namespace holmes::bson {

bool value::is_null() const {
	return false;
}

value& value::operator*() {
	return *this;
}

const value& value::operator*() const {
	return *this;
}

any& value::at(const std::string& name) {
	throw std::runtime_error("BSON value does not support indexing by string");
}

const any& value::at(const std::string& name) const {
	throw std::runtime_error("BSON value does not support indexing by string");
}

any& value::at(size_t index) {
	throw std::runtime_error("BSON value does not support indexing by integer");
}

const any& value::at(size_t index) const {
	throw std::runtime_error("BSON value does not support indexing by integer");
}

} /* namespace holmes::bson */
