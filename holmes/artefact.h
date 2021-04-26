// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_ARTEFACT
#define HOLMES_ARTEFACT

#include "holmes/bson/document.h"

namespace holmes {

/** An abstract base class to represent a decoded artefact. */
class artefact {
public:
	/** Describe this artefact using BSON.
	 * @return a BSON description of this artefact.
	 */
	virtual bson::document to_bson() const = 0;
};

} /* namespace holmes */

#endif
