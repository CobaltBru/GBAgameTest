
#ifndef MAT4_HPP
# define MAT4_HPP

# include "fixed.hpp"
# include "vec4.hpp"
# include <cstdint>

/* 임시 타입 정의*/
typedef uint32_t	u32;


struct mat4 {
	fixed	element[16];

	mat4	operator+(mat4 const &other) const;
	mat4	operator-(mat4 const &other) const;
	mat4	operator*(fixed const &other) const;
	mat4	operator*(mat4 const &other) const;
	vec4	operator*(vec4 const &other) const;
	static mat4	identity();
	static mat4	transpose(mat4 const &matrix);
	static mat4	translate(fixed x, fixed y, fixed z);
	static mat4	rotateX(int angle);
	static mat4	rotateY(int angle);
	static mat4	rotateZ(int angle);
	static mat4	scale(fixed x, fixed y, fixed z);
};

#endif
