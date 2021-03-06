// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#ifndef HOLMES_BSON_ANY
#define HOLMES_BSON_ANY

#include "holmes/bson/value.h"

namespace holmes::bson {

class null;

/** A class to represent a BSON value of any type. */
class any:
	public value {
private:
	/** A pointer to a shared copy of the null value. */
	static holmes::bson::value* _null;

	/** A pointer to the heap-allocated value of this object. */
	value* _ptr;
public:
	/** Construct null value. */
	any():
		_ptr(_null) {}

	/** Copy-construct from another bson::any.
	 * @param that the value to be copied
	 */
	any(const any& that):
		_ptr(that.clone().release()) {}

	/** Move-construct from another bson::any.
	 * @param that the value to be moved
	 */
	any(any&& that):
		_ptr(that._ptr) {

		that._ptr = _null;
	}

	/** Copy-assign from another bson::any.
	 * @param that the value to be copied
	 * @return a reference to this
	 */
	any& operator=(const any& that) {
		if (this != &that) {
			if (_ptr != _null) {
				delete _ptr;
			}
			_ptr = that.clone().release();
		}
		return *this;
	}

	/** Move-assign from another bson::any.
	 * @param that the value to be moved
	 * @return a reference to this
	 */
	any& operator=(any&& that) {
		if (this != &that) {
			if (_ptr != _null) {
				delete _ptr;
			}
			_ptr = that._ptr;
			that._ptr = _null;
		}
		return *this;
	}

	/** Copy construct from any type of bson::value.
	 * @param that the value to be copied
	 */
	explicit any(const value& that):
		_ptr((*that).clone().release()) {}

	/** Copy assign from any type of bson::value.
	 * @param that the value to be copied
	 */
	any& operator=(const value& that) {
		if (this != &that) {
			if (_ptr != _null) {
				delete _ptr;
			}
			_ptr = (*that).clone().release();
		}
		return *this;
	}

	/** Decode from an octet string.
	 * @param type the required object type
	 * @param bd the BSON data to be decoded
	 * @return the resulting BSON value
	 */
	any(unsigned char type, octet::string& bd);

	/** Destroy this value. */
	~any() override {
		if (_ptr != _null) {
			delete _ptr;
		}
	}

	std::unique_ptr<value> clone() const override;
	unsigned char type() const override;
	size_t length() const override;
	bool is_null() const override;
	void encode(writer& bw) const override;
	std::string to_json() const override;

	value& operator*() override;
	const value& operator*() const override;
	operator bool() const override;
	operator int64_t() const override;
	operator std::string() const override;
	operator octet::string() const override;
	any& at(const std::string& name) override;
	const any& at(const std::string& name) const override;
};

} /* namespace holmes::bson */

#endif
