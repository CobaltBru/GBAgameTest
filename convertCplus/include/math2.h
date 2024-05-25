#pragma once

#include <string.h>
#include <math.h>
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "fixed.hpp"

// #define PI_FLT 3.14159265f
#define TAU 0xFFFF
#define PI 0x8000 // round(TAU / 2)
#define ONE_DEGREE  0xB6
#define FIXED_12_SCALE (1 << 12)

fixed getRadian(fixed num);

mat4 matrix4x4createRotX(int angle);
mat4 matrix4x4createRotY(int angle);
mat4 matrix4x4createRotZ(int angle);

//void matrix4x4SetBasis(FIXED matrix[16], VECTOR x, VECTOR y, VECTOR z); //행렬 만들기

void matrix4x4rotateYPR(mat4 &matrix,int yaw, int pitch, int roll); //회전
void matrix4x4SetTranslation(mat4 &matrix, vec4 trans); //이동

vec3 vecCross(vec3 a, vec3 b);

void	sincos(int angle, fixed &sine, fixed &cosine);

fixed ABS(fixed number);
