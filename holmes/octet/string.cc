// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <cstring>
#include <iomanip>

#include "holmes/octet/heap_buffer.h"
#include "holmes/octet/string.h"

namespace holmes::octet {

std::unique_ptr<buffer> string::_empty_buffer(new(0) heap_buffer);

string::string(const string& that, size_type index, size_type length):
	_buffer(buffer::link(*that._buffer)) {

	if (index > that.length()) {
		index = that.length();
	}
	if (length > that.length() - index) {
		length = that.length() - index;
	}
	this->_data = that._data + index;
	this->_length = length;
}

string::string(const unsigned char* data, size_type length):
	_buffer(new(length) heap_buffer),
	_data(_buffer->data()),
	_length(length) {

	std::memcpy(_buffer->data(), data, length);
}

class hex_format {
private:
	std::ostream* _out;
	std::ios_base::fmtflags _flags;
	char _fill;
public:
	hex_format(std::ostream& out);
	~hex_format();
};

hex_format::hex_format(std::ostream& out):
	_out(&out),
	_flags(out.flags()),
	_fill(out.fill()) {

	_out->setf(std::ios_base::hex, std::ios_base::basefield);
	_out->fill('0');
}

hex_format::~hex_format() {
	_out->fill(_fill);
	_out->flags(_flags);
}

std::ostream& operator<<(std::ostream& out, const string& octets) {
	hex_format hf(out);
	for (auto octet : octets) {
		out.width(2);
		out << (octet & 0xff);
	}
	return out;
}

} /* namespace holmes::octet */
