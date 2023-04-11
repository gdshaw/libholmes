// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_FEATURE_LOGGER
#define HOLMES_FEATURE_LOGGER

#include <memory>
#include <list>

#include "holmes/feature.h"
#include "holmes/bson/array.h"

namespace holmes {

/** A class for recording features observed while inspecting an artefact. */
class feature::logger {
private:
	/** The path to be used when new features are recorded.
	 * The path identifies the artefact to which an feature refers.
	 */
	std::string _path;

	/** The recorded features, or null to discard. */
	std::shared_ptr<std::list<feature>> _features;
public:
	/** Construct a feature logger for a top-level artefact. */
	logger() = default;

	/** Construct a feature logger for a top-level artefact.
	 * @param features a list for accumulating logged features
	 */
	logger(std::shared_ptr<std::list<feature>> features):
		_features(features) {}

	/** Construct a feature logger for a constituent artefact.
	 * @param parent a logger for the parent artefact
	 * @param subpath a subpath identifying the relevant artefact
	 *  with respect to the parent artefact
	 */
	logger(logger& parent, const std::string& subpath);

	/** Record a feature.
	 * @param feature_type an identifier which uniquely identifies the
	 *  type of feature to be recorded
	 */
	void log(const std::string& feature_type);

	/** Convert the logged features to BSON.
	 * @return the logged features as BSON
	 */
	bson::array to_bson() const;
};

} /* namespace holmes */

#endif
