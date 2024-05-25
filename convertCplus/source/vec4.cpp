
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

vec4	vec4::operator*(fixed other) const {
	return (vec4(this->x * other, this->y * other, this->z * other, this->w * other));
}

vec4	vec4::operator/(fixed other) const {
	return (vec4(this->x / other, this->y / other, this->z / other, this->w / other));
}

vec4	vec4::normalize(vec4 const &a)
{
	fixed inv_hypot = fixed(1) / fixed::sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w));
	return {a.x * inv_hypot, a.y * inv_hypot, a.z * inv_hypot, a.w * inv_hypot};
}

fixed	vec4::dot(vec4 const &a, vec4 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

vec4	vec4::one() {
	return {1, 1, 1, 1};
}
