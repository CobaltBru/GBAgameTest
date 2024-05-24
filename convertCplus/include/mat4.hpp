#include "fixed.hpp"

#ifndef MAT4_HPP
# define MAT4_HPP

/* 임시 타입 정의*/
typedef unsigned int	u32;


struct mat4 {
	fixed	element[16];

	mat4(); // zero-initialized
	mat4	operator+(mat4 const &other) const;
	mat4	operator-(mat4 const &other) const;
	mat4	operator*(fixed const &other) const;
	mat4	operator*(mat4 const &other) const;
	static mat4	identity();
};

#endif
