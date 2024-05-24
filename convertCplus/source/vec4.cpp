
#include "vec4.hpp"

vec4::vec4(): x(), y(), z(), w() {}
vec4::vec4(fixed x, fixed y, fixed z, fixed w): x(x), y(y), z(z), w(w) {}

vec4	vec4::operator+(vec4 const &other) const {
	vec4 const	ret = {
		this->x + other.x,
		this->y + other.y,
		this->z + other.z,
		this->w + other.w
	};

	return (ret);
}

vec4	vec4::operator-(vec4 const &other) const {
	vec4 const	ret = {
		this->x - other.x,
		this->y - other.y,
		this->z - other.z,
		this->w - other.w
	};

	return (ret);
}

vec4	vec4::operator*(vec4 const &other) const {
	vec4 const	ret = {
		this->x * other.x,
		this->y * other.y,
		this->z * other.z,
		this->w * other.w
	};

	return (ret);
}

vec4	vec4::operator/(vec4 const &other) const {
	vec4 const	ret = {
		this->x / other.x,
		this->y / other.y,
		this->z / other.z,
		this->w / other.w
	};

	return (ret);
}

fixed	vec4::dot(vec4 const &a, vec4 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

vec4	vec4::zero() {
	vec4	ret = {0, 0, 0, 0};

	return (ret);
}

vec4	vec4::one() {
	vec4	ret = {1, 1, 1, 1};

	return (ret);
}
