// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/feature/logger.h"

namespace holmes {

feature::logger::logger(logger& parent, const std::string& subpath):
	_path(parent._path + (parent._path.empty() ? "" : ".") + subpath),
	_features(parent._features) {}

void feature::logger::log(const std::string& feature_type) {
	if (_features) {
		_features->push_back(feature(feature_type, _path));
	}
}

bson::array feature::logger::to_bson() const {
	bson::array bson_features;
	for (auto& feature: *_features) {
		bson_features.append(feature.to_bson());
	}
	return bson_features;
}

} /* namespace holmes */
