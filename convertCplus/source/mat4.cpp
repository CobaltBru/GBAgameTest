
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

vec4	mat4::operator*(vec4 const &other) const {
	vec4	ret = {
		this->element[0] * other.x + this->element[1] * other.y + this->element[2] * other.z + this->element[3] * other.w,
		this->element[4] * other.x + this->element[5] * other.y + this->element[6] * other.z + this->element[7] * other.w,
		this->element[8] * other.x + this->element[9] * other.y + this->element[10] * other.z + this->element[11] * other.w,
		this->element[12] * other.x + this->element[13] * other.y + this->element[14] * other.z + this->element[15] * other.w,
	};
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

mat4	mat4::transpose(mat4 const &matrix) {
	mat4	ret = {
		matrix.element[0], matrix.element[4], matrix.element[8], matrix.element[12],
		matrix.element[1], matrix.element[5], matrix.element[9], matrix.element[13],
		matrix.element[2], matrix.element[6], matrix.element[10], matrix.element[14],
		matrix.element[3], matrix.element[7], matrix.element[11], matrix.element[15],
	};
	return (ret);
}
// 예스
// 선언만 해두시면 제가 만들겠습니다
// 이거 사인코사인을 tonc에 의존하고 있었는데 이것도 만들어야겠네여
// 넹