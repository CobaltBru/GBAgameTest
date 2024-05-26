
#include "vec3.hpp"

vec3	vec3::operator-() const {
	return {-this->x, -this->y, -this->z};
}

vec3	vec3::operator+(vec3 const &other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z};
}

vec3	vec3::operator-(vec3 const &other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z};
}

vec3	vec3::operator*(vec3 const &other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z};
}

vec3	vec3::operator/(vec3 const &other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z};
}

vec3	vec3::operator*(fixed other) const {
	return {this->x * other, this->y * other, this->z * other};
}

vec3	vec3::operator/(fixed other) const {
	return {this->x / other, this->y / other, this->z / other};
}

vec3	vec3::one() {
	return {1, 1, 1};
}