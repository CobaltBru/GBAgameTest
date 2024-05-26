
#include "mat4.hpp"
#include "math2.hpp"

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
			ret.element[r * 4 + c] = 0;
			for (u32 i = 0; i < 4; ++i) {
				ret.element[r * 4 + c] += this->element[r * 4 + i] * other.element[i * 4 + c];
			}
		}
	}
	return (ret);
}

vec4	mat4::operator*(vec4 const &other) const {
	return {
		this->element[0] * other.x + this->element[1] * other.y + this->element[2] * other.z + this->element[3] * other.w,
		this->element[4] * other.x + this->element[5] * other.y + this->element[6] * other.z + this->element[7] * other.w,
		this->element[8] * other.x + this->element[9] * other.y + this->element[10] * other.z + this->element[11] * other.w,
		this->element[12] * other.x + this->element[13] * other.y + this->element[14] * other.z + this->element[15] * other.w,
	};
}

mat4	mat4::identity() {
	mat4	ret;

	ret.element[0] = 1;
	ret.element[5] = 1;
	ret.element[10] = 1;
	ret.element[15] = 1;
	return (ret);
}

mat4	mat4::transpose(mat4 const &matrix) {
	mat4	ret = {
		matrix.element[0], matrix.element[4], matrix.element[8], matrix.element[12],
		matrix.element[1], matrix.element[5], matrix.element[9], matrix.element[13],
		matrix.element[2], matrix.element[6], matrix.element[10], matrix.element[14],
		matrix.element[3], matrix.element[7], matrix.element[11], matrix.element[15],
	};
	return (ret);
}

mat4	mat4::translate(fixed x, fixed y, fixed z) {
	return {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

mat4	mat4::rotateX(int angle) {
	vec2	t = sincos(angle);

	return {
		1, 0, 0, 0,
		0, t.x, t.y, 0,
		0, -t.y, t.x, 0,
		0, 0, 0, 1
	};
}

mat4	mat4::rotateY(int angle) {
	vec2	t = sincos(angle);

	return {
		t.x, 0, -t.y, 0,
		0, 1, 0, 0,
		t.y, 0, t.x, 0,
		0, 0, 0, 1
	};
}

mat4	mat4::rotateZ(int angle) {
	vec2	t = sincos(angle);

	return {
		t.x, -t.y, 0, 0,
		t.y, t.x, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

mat4	mat4::scale(fixed x, fixed y, fixed z) {
	return {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}
