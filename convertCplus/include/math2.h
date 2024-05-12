#pragma once

#include <tonc.h>

// #define PI_FLT 3.14159265f
#define TAU 0xFFFF
#define PI 0x8000 // round(TAU / 2)
#define ONE_DEGREE  0xB6
#define FIXED_12_SCALE (1 << 12)

typedef s32 FIXED_12;
typedef FIXED_12 ANGLE_FIXED_12;
typedef struct s_obj t_obj;


struct s_obj
{
    VECTOR vertex[512];
    int index[512];
    int v_size;
    int i_size;
};
FIXED getRadian(FIXED num);

FIXED matrix4x4Get(const FIXED matrix[16], int row, int col);
void matrix4x4Set(FIXED matrix[16], int row, int col, FIXED value);

void matrix4x4Transpose(FIXED mat[16]);
void matrix4x4Mul(FIXED a[16], const FIXED b[16]);
void matrix4x4createRotX(FIXED matrix[16], ANGLE_FIXED_12 angle);
void matrix4x4createRotY(FIXED matrix[16], ANGLE_FIXED_12 angle);
void matrix4x4createRotZ(FIXED matrix[16], ANGLE_FIXED_12 angle);

void matrix4x4SetBasis(FIXED matrix[16], VECTOR x, VECTOR y, VECTOR z); //행렬 만들기
void matrix4x4setIdentity(FIXED matrix[16]); //행렬 초기화
void matrix4x4scaler(FIXED matrix[16],FIXED scale); //확대축소
void matrix4x4rotateYPR(FIXED matrix[16],VECTOR rotate); //회전
void matrix4x4SetTranslation(FIXED matrix[16], VECTOR trans); //이동

VECTOR vecTransformed(const FIXED matrix[16], VECTOR vec); //벡터에 행렬 적용
VECTOR vecScaled(VECTOR vec, FIXED factor);
void vecScale(VECTOR *vec, FIXED factor);
VECTOR vecAdd(VECTOR a, VECTOR b);
VECTOR vecSub(VECTOR a, VECTOR b);
VECTOR vecUnit(VECTOR a);
FIXED vecMag(VECTOR a);
VECTOR vecCross(VECTOR a, VECTOR b);
FIXED vecDot(VECTOR a, VECTOR b);


INLINE FIXED_12 int2fx12(int num) {
    return (ANGLE_FIXED_12) num << 12;
}

INLINE FIXED_12 fx2fx12(FIXED num) { // invariant: FIX_SHIFT <= 12
    return num << (12 - FIX_SHIFT);
}
INLINE FIXED fx12Tofx(FIXED_12 num) {  // invariant: FIX_SHIFT <= 12
      return (FIXED)num >> (12 - FIX_SHIFT); // CAREFUL: usual arithmetic conversions promote the signed int to unsigned
 }

INLINE int fx12ToInt(FIXED_12 num) {
     return num >> 12;
 }

INLINE float fx12ToFloat(FIXED_12 num) {
     return num / (float)FIXED_12_SCALE;
 }

INLINE FIXED_12 float2fx12(float num) {
    return (FIXED_12) (num * FIXED_12_SCALE);
}

INLINE FIXED_12 fx12mul(FIXED_12 a, FIXED_12 b) {
    return (a * b) >> 12;
}

INLINE FIXED_12 fx12div(FIXED_12 a, FIXED_12 b) {
    return (a * FIXED_12_SCALE) / b;
}

INLINE FIXED cosFx(ANGLE_FIXED_12 alpha) {
    return fx12Tofx(lu_cos(ABS(alpha) & 0xffff) );
}

INLINE FIXED sinFx(FIXED_12 alpha) {
    return alpha < 0 ? -fx12Tofx(lu_sin(ABS(alpha) & 0xffff) ) : fx12Tofx(lu_sin(alpha & 0xffff));
}