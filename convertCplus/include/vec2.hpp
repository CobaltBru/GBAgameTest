
#ifndef VEC4_HPP
# define VEC4_HPP

#include "fixed.hpp"

struct vec2
{
	fixed	x;
	fixed	y;

	vec2();
	vec2(fixed x, fixed y);

	vec2	operator-() const;

	vec2	operator+(vec2 const &other) const;
	vec2	operator-(vec2 const &other) const;
	vec2	operator*(vec2 const &other) const;
	vec2	operator/(vec2 const &other) const; //element-wise arithmetic
	
	vec2	operator*(fixed other) const;
	vec2	operator/(fixed other) const; //constant-scaling
	
	static vec2		normalize(vec2 const &a);
	static fixed	dot(vec2 const &a, vec2 const &b);
	static vec2		one();
};


#endif
