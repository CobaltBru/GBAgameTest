
#ifndef VEC4_HPP
# define VEC4_HPP

#include "fixed.hpp"

struct vec4
{
	fixed	x;
	fixed	y;
	fixed	z;
	fixed	w;
	
	vec4	operator-() const;

	vec4	operator+(vec4 const &other) const;
	vec4	operator-(vec4 const &other) const;
	vec4	operator*(vec4 const &other) const;
	vec4	operator/(vec4 const &other) const; //element-wise arithmetic
	
	vec4	operator*(fixed other) const;
	vec4	operator/(fixed other) const; //constant-scaling

	static vec4	one();
};


#endif
