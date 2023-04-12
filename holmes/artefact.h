// This file is part of libholmes.
// Copyright 2021-23 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_ARTEFACT
#define HOLMES_ARTEFACT

#include "holmes/validation_policy.h"
#include "holmes/feature/logger.h"
#include "holmes/bson/document.h"

namespace holmes {

/** An abstract base class to represent a decoded artefact. */
class artefact {
protected:
	/** Validate this artifact.
	 * @param policy the validation policy to be applied
	 * @param log a logger for recording the results
	 * @return true if valid, otherwise false
	 */
	virtual bool _validate(const validation_policy& policy,
		feature::logger& log) const;
public:
	bool validate(const validation_policy& policy, feature::logger& log) const {
		return _validate(policy, log);
	}

	/** Describe this artefact using BSON.
	 * @return a BSON description of this artefact.
	 */
	virtual bson::document to_bson() const = 0;
};

} /* namespace holmes */

#endif
