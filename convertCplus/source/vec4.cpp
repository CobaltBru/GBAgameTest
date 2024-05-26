
#include "vec4.hpp"

vec4	vec4::operator-() const {
	return {-this->x, -this->y, -this->z, -this->w};
}

vec4	vec4::operator+(vec4 const &other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
}

vec4	vec4::operator-(vec4 const &other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
}

vec4	vec4::operator*(vec4 const &other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w};
}

vec4	vec4::operator/(vec4 const &other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w};
}

vec4	vec4::operator*(fixed other) const {
	return {this->x * other, this->y * other, this->z * other, this->w * other};
}

vec4	vec4::operator/(fixed other) const {
	return {this->x / other, this->y / other, this->z / other, this->w / other};
}

vec4	vec4::one() {
	return {1, 1, 1, 1};
}
