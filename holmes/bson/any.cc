// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include "holmes/bson/string.h"
#include "holmes/bson/document.h"
#include "holmes/bson/array.h"
#include "holmes/bson/binary.h"
#include "holmes/bson/boolean.h"
#include "holmes/bson/null.h"
#include "holmes/bson/int32.h"
#include "holmes/bson/int64.h"
#include "holmes/bson/any.h"

namespace holmes::bson {

bson::value* any::_null = new bson::null;

any::any(unsigned char type, octet::string& bd) {
	switch (type) {
	case 0x02:
		_ptr = new bson::string(bd, decode());
		break;
	case 0x03:
		_ptr = new bson::document(bd, decode());
		break;
	case 0x04:
		_ptr = new bson::array(bd, decode());
		break;
	case 0x05:
		_ptr = new bson::binary(bd, decode());
		break;
	case 0x08:
		_ptr = new bson::boolean(bd, decode());
		break;
	case 0x0a:
		_ptr = _null;
		break;
	case 0x10:
		_ptr = new bson::int32(bd, decode());
		break;
	case 0x12:
		_ptr = new bson::int64(bd, decode());
		break;
	default:
		throw std::invalid_argument("unsupported BSON type code");
	}
}

std::unique_ptr<value> any::clone() const {
	return _ptr->clone();
}

unsigned char any::type() const {
	return _ptr->type();
}

size_t any::length() const {
	return _ptr->length();
}

bool any::is_null() const {
	return _ptr->is_null();
}

void any::encode(writer& bw) const {
	return _ptr->encode(bw);
}

std::string any::to_json() const {
	return _ptr->to_json();
}

value& any::operator*() {
	return *_ptr;
}

const value& any::operator*() const {
	return *_ptr;
}

any::operator bool() const {
	return _ptr->operator bool();
}

any::operator int64_t() const {
	return _ptr->operator int64_t();
}

any::operator std::string() const {
	return _ptr->operator std::string();
}

any::operator octet::string() const {
	return _ptr->operator octet::string();
}

any& any::at(const std::string& name) {
	return _ptr->at(name);
}

const any& any::at(const std::string& name) const {
	return _ptr->at(name);
}

} /* namespace holmes::bson */
