#include <string.h>
#include <cmath>
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "fixed.hpp"
// #define PI_FLT 3.14159265f
#define TAU 0xFFFF
#define PI 0x8000 // round(TAU / 2)
#define ONE_DEGREE  0xB6
#define FIXED_12_SCALE (1 << 12)

fixed getRadian(fixed num);


//void matrix4x4SetBasis(FIXED matrix[16], VECTOR x, VECTOR y, VECTOR z); //행렬 만들기


vec3 vecCross(vec3 a, vec3 b);


fixed	sqrt(fixed f);
fixed	abs(fixed f);
vec2	sincos(int angle);

fixed	dot(vec2 const &a, vec2 const &b);
fixed	dot(vec3 const &a, vec3 const &b);
fixed	dot(vec4 const &a, vec4 const &b);

vec3	cross(vec3 const &a, vec3 const &b);

fixed	length(vec2 const &a);
fixed	length(vec3 const &a);
fixed	length(vec4 const &a);

vec2	normalize(vec2 const &a);
vec3	normalize(vec3 const &a);
vec4	normalize(vec4 const &a);
