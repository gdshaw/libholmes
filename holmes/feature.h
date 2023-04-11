// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_FEATURE
#define HOLMES_FEATURE

#include "holmes/bson/document.h"

namespace holmes {

/** A class to represent a feature of an artefact. */
class feature {
private:
	/** The feature type. */
	std::string _type;

	/** The artefact path.
	 * This identifies the artefact to which the feature refers.
	 */
	std::string _path;
public:
	/** Construct feature.
	 * @param type the feature type
	 * @param path the artifact path
	 */
	feature(const std::string& type, const std::string& path):
		_type(type), _path(path) {}


	/** Get the type of this feature.
	 * @return the feature type
	 */
	const std::string& type() const {
		return _type;
	}

	/** Get the path of the artefact to which this feature refers.
	 * @return the artefact path
	 */
	const std::string& path() const {
		return _path;
	}

	/** Convert this feature to BSON.
	 * @return this feature as BSOB
	 */
	bson::document to_bson() const;
};

} /* namespace holmes */

#endif
