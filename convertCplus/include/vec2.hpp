
#ifndef VEC2_HPP
# define VEC2_HPP

#include "fixed.hpp"

struct vec2
{
	fixed	x;
	fixed	y;

	vec2	operator-() const;

	vec2	operator+(vec2 const &other) const;
	vec2	operator-(vec2 const &other) const;
	vec2	operator*(vec2 const &other) const;
	vec2	operator/(vec2 const &other) const; //element-wise arithmetic
	
	vec2	operator*(fixed other) const;
	vec2	operator/(fixed other) const; //constant-scaling

	static vec2	one();
};


#endif
