
#ifndef vec3_HPP
# define vec3_HPP

#include "fixed.hpp"

struct vec3
{
	fixed	x;
	fixed	y;
	fixed	z;
	
	vec3	operator-() const;

	vec3	operator+(vec3 const &other) const;
	vec3	operator-(vec3 const &other) const;
	vec3	operator*(vec3 const &other) const;
	vec3	operator/(vec3 const &other) const; //element-wise arithmetic
	
	vec3	operator*(fixed other) const;
	vec3	operator/(fixed other) const; //constant-scaling

	static vec3		one();
};


#endif