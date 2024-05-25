
#include "vec2.hpp"

vec2::vec2(): x(), y() {}
vec2::vec2(fixed x, fixed y): x(x), y(y) {}

vec2	vec2::operator-() const {
	return {-this->x, -this->y};
}

vec2	vec2::operator+(vec2 const &other) const {
	vec2 const	ret = {
		this->x + other.x,
		this->y + other.y,
	};

	return (ret);
}

vec2	vec2::operator-(vec2 const &other) const {
	vec2 const	ret = {
		this->x - other.x,
		this->y - other.y,
	};

	return (ret);
}

vec2	vec2::operator*(vec2 const &other) const {
	vec2 const	ret = {
		this->x * other.x,
		this->y * other.y,
	};

	return (ret);
}

vec2	vec2::operator/(vec2 const &other) const {
	vec2 const	ret = {
		this->x / other.x,
		this->y / other.y,
	};

	return (ret);
}

vec2	vec2::operator*(fixed other) const {
	return (vec2(this->x * other, this->y * other));
}

vec2	vec2::operator/(fixed other) const {
	return (vec2(this->x / other, this->y / other));
}

vec2	vec2::normalize(vec2 const &a)
{
	fixed const inv_hypot = fixed(1) / fixed::sqrt((a.x * a.x) + (a.y * a.y));

	return {a.x * inv_hypot, a.y * inv_hypot};
}

fixed	vec2::dot(vec2 const &a, vec2 const &b) {
	return (a.x * b.x + a.y * b.y);
}

vec2	vec2::one() {
	return {1, 1};
}
