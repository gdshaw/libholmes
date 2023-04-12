// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_VALIDATION_POLICY
#define HOLMES_VALIDATION_POLICY

namespace holmes {

/** A class for specifying how an artefact should be validated. */
class validation_policy {
public:
	static const validation_policy default_policy;
};

} /* namespace holmes */

#endif
