
#include "vec2.hpp"

vec2	vec2::operator-() const {
	return {-this->x, -this->y};
}

vec2	vec2::operator+(vec2 const &other) const {
	return {this->x + other.x, this->y + other.y};
}

vec2	vec2::operator-(vec2 const &other) const {
	return {this->x - other.x, this->y - other.y};
}

vec2	vec2::operator*(vec2 const &other) const {
	return {this->x * other.x, this->y * other.y};
}

vec2	vec2::operator/(vec2 const &other) const {
	return {this->x / other.x, this->y / other.y};
}

vec2	vec2::operator*(fixed other) const {
	return {this->x * other, this->y * other};
}

vec2	vec2::operator/(fixed other) const {
	return {this->x / other, this->y / other};
}

vec2	vec2::one() {
	return {1, 1};
}
