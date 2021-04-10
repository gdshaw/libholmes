// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <holmes/parse_error.h>

namespace holmes {

parse_error::parse_error(const std::string& message):
	std::runtime_error(message) {}

} /* namespace holmes */
