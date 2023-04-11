// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/feature.h"
#include "holmes/bson/string.h"

namespace holmes {

bson::document feature::to_bson() const {
	bson::document bson_feature;
	bson_feature.append("type", bson::string(_type));
	bson_feature.append("path", bson::string(_path));
	return bson_feature;
}

} /* namespace holmes */
