
#include "mat4.hpp"

mat4::mat4(): element() {}

mat4	mat4::operator+(mat4 const &other) const {
	mat4	ret;

	for (u32 r = 0; r < 4; ++r) {
		for (u32 c = 0; c < 4; ++c) {
			ret.element[r * 4 + c] = this->element[r * 4 + c] + other.element[r * 4 + c];
		}
	}
	return (ret);
}

mat4	mat4::operator-(mat4 const &other) const {
	mat4	ret;

	for (u32 r = 0; r < 4; ++r) {
		for (u32 c = 0; c < 4; ++c) {
			ret.element[r * 4 + c] = this->element[r * 4 + c] - other.element[r * 4 + c];
		}
	}
	return (ret);
}

mat4	mat4::operator*(fixed const &other) const {
	mat4	ret;

	for (u32 r = 0; r < 4; ++r) {
		for (u32 c = 0; c < 4; ++c) {
			ret.element[r * 4 + c] = this->element[r * 4 + c] * other;
		}
	}
	return (ret);
}

mat4	mat4::operator*(mat4 const &other) const {
	mat4	ret;

	for (u32 r = 0; r < 4; ++r) {
		for (u32 c = 0; c < 4; ++c) {
			for (u32 i = 0; i < 4; ++i) {
				ret.element[r * 4 + c] += this->element[r * 4 + i] * other.element[i * 4 + c];
			}
		}
	}
	return (ret);
}

mat4	mat4::identity() {
	mat4	ret;

	ret.element[0] = 1;
	ret.element[5] = 1;
	ret.element[10] = 1;
	ret.element[15] = 1;
	return (ret);
}
