
#include "vec3.hpp"

vec3::vec3(): x(), y(), z() {}
vec3::vec3(fixed x, fixed y, fixed z): x(x), y(y), z(z) {}

vec3	vec3::operator+(vec3 const &other) const {
	vec3 const	ret = {
		this->x + other.x,
		this->y + other.y,
		this->z + other.z
	};

	return (ret);
}

vec3	vec3::operator-(vec3 const &other) const {
	vec3 const	ret = {
		this->x - other.x,
		this->y - other.y,
		this->z - other.z
	};

	return (ret);
}

vec3	vec3::operator*(vec3 const &other) const {
	vec3 const	ret = {
		this->x * other.x,
		this->y * other.y,
		this->z * other.z
	};

	return (ret);
}

vec3	vec3::operator/(vec3 const &other) const {
	vec3 const	ret = {
		this->x / other.x,
		this->y / other.y,
		this->z / other.z
	};

	return (ret);
}

vec3	vec3::operator*(fixed other) const {
	return (vec3(this->x * other, this->y * other, this->z * other));
}

vec3	vec3::operator/(fixed other) const {
	return (vec3(this->x / other, this->y / other, this->z / other));
}

vec3	vec3::normalize(vec3 const &a)
{
	fixed tmp = fixed::sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	return {a.x / tmp, a.y / tmp, a.z / tmp};
}

fixed	vec3::dot(vec3 const &a, vec3 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

vec3	vec3::one() {
	vec3	ret = {1, 1, 1};

	return (ret);
}