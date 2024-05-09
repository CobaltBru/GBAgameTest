#pragma once

#include <tonc.h>
#include <math.h>

#include "math.h"


FIXED getRadian(FIXED num)
{
    return fxmul(num,fxdiv(PI,180.0f));
}

VECTOR make_vector(FIXED x, FIXED y, FIXED z)
{
    VECTOR tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    return tmp;
}

// void print_obj(const t_obj* obj)
// {
//     printf("size: %d\n", obj->size);
//     for(int i = 0;i<obj->size;i++)
//     {
//         printf("%f ,%f ,%f \n",obj->vertex[i].x,obj->vertex[i].y,obj->vertex[i].z);
//     }
//     printf("\n");
// }

VECTOR vecTransformed(const FIXED matrix[16], VECTOR vec) //행렬 변환을 적용
{
    VECTOR transformed;
    transformed.x = fxmul(vec.x,matrix[0]) + fxmul(vec.y,matrix[1]) + fxmul(vec.z,matrix[2]) + matrix[3];
    transformed.y = fxmul(vec.x,matrix[4]) + fxmul(vec.y,matrix[5]) + fxmul(vec.z,matrix[6]) + matrix[7];
    transformed.z = fxmul(vec.x,matrix[8]) + fxmul(vec.y,matrix[9]) + fxmul(vec.z,matrix[10]) + matrix[11];
    FIXED w = fxmul(vec.x , matrix[12]) + fxmul(vec.x , matrix[13]) + fxmul(vec.x , matrix[14]) + matrix[15];

    if(w != int2fx(1))
    {
        transformed.x = fxdiv(transformed.x, w);
        transformed.y = fxdiv(transformed.y, w);
        transformed.z = fxdiv(transformed.z, w); 
    }
    return transformed;
}

void vecTransform(const FIXED matrix[16], VECTOR* vec) //행렬 변환을 적용
{
    VECTOR transformed;
    transformed.x = fxmul(vec->x,matrix[0]) + fxmul(vec->y,matrix[1]) + fxmul(vec->z,matrix[2]) + matrix[3];
    transformed.y = fxmul(vec->x,matrix[4]) + fxmul(vec->y,matrix[5]) + fxmul(vec->z,matrix[6]) + matrix[7];
    transformed.z = fxmul(vec->x,matrix[8]) + fxmul(vec->y,matrix[9]) + fxmul(vec->z,matrix[10]) + matrix[11];
    FIXED w = fxmul(vec->x , matrix[12]) + fxmul(vec->x , matrix[13]) + fxmul(vec->x , matrix[14]) + matrix[15];
    *vec = transformed;
    if(w != int2fx(1))
    {
        vec->x = fxdiv(transformed.x, w);
        vec->y = fxdiv(transformed.y, w);
        vec->z = fxdiv(transformed.z, w); 
    }
}

FIXED matrix4x4Get(const FIXED matrix[16], int row, int col) 
{
    return matrix[row * 4 + col];
}

void matrix4x4Set(FIXED matrix[16], int row, int col, FIXED value) 
{
    matrix[row * 4 + col] = value;
}

void matrix4x4Mul(FIXED a[16], const FIXED b[16]) 
{
    FIXED result[16];
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            FIXED value = int2fx(0);
            for (int i = 0; i < 4; ++i) {
                value = value + fxmul(matrix4x4Get(a, row, i), matrix4x4Get(b, i, col));
            }
            matrix4x4Set(result, row, col, value);
        }
    }
    memcpy(a, result, sizeof(result));
}

void matrix4x4setIdentity(FIXED matrix[16]) 
{
    memset(matrix, 0, sizeof(*matrix) * 16);
    matrix[0] = int2fx(1);
    matrix[5] = int2fx(1);
    matrix[10] = int2fx(1);
    matrix[15] = int2fx(1);
}

void matrix4x4scaler(FIXED matrix[16],VECTOR scale) //확대축소
{
    matrix[0] = scale.x;
    matrix[5] = scale.y;
    matrix[10] = scale.z;
}
void matrix4x4createRotX(FIXED matrix[16], ANGLE_FIXED_12 angle) 
{
    matrix4x4setIdentity(matrix);
    // x y z tx
    // x y z ty
    // x y z tz
    // 0 0 0 w
    // y-basis
    matrix[5] = cosFx(angle);
    matrix[9] = sinFx(angle); // minus
    // z-basis
    matrix[6] = -sinFx(angle); // plus
    matrix[10] = cosFx(angle);
}

void matrix4x4createRotY(FIXED matrix[16], ANGLE_FIXED_12 angle) 
{
    matrix4x4setIdentity(matrix);
    // x-basis
    matrix[0] = cosFx(angle);
    matrix[8] = -sinFx(angle);
    // z-basis
    matrix[2] = sinFx(angle);
    matrix[10] = cosFx(angle);
}

void matrix4x4createRotZ(FIXED matrix[16], ANGLE_FIXED_12 angle) 
{
    matrix4x4setIdentity(matrix);
    // x-basis
    matrix[0] = cosFx(angle);
    matrix[4] = sinFx(angle);
    // y-basis
    matrix[1] = -sinFx(angle);
    matrix[5] = cosFx(angle);
}
void matrix4x4rotateYPR(FIXED matrix[16],VECTOR rotate) //회전
{
    FIXED tmp[16];
    rotate.x = getRadian(rotate.x);
    rotate.y = getRadian(rotate.y);
    rotate.z = getRadian(rotate.z);
    matrix4x4setIdentity(tmp);
    tmp[0] = (cosf(rotate.z) * cosf(rotate.x)) + (sinf(rotate.z)*sinf(rotate.x)*sinf(rotate.y));
    tmp[1] = -(sinf(rotate.z) * cosf(rotate.x)) + (cosf(rotate.z)*sinf(rotate.x)*sinf(rotate.y));
    tmp[2] = sinf(rotate.x) * cosf(rotate.y);

    tmp[4] = sinf(rotate.z) * cosf(rotate.y);
    tmp[5] = cosf(rotate.z) * cosf(rotate.y);
    tmp[6] = -sinf(rotate.y);

    tmp[8] = (-cosf(rotate.z) * sinf(rotate.z)) + (sinf(rotate.z)*cosf(rotate.x)*sinf(rotate.y));
    tmp[9] = (sinf(rotate.z) * sinf(rotate.z)) + (cosf(rotate.z)*cosf(rotate.x)*sinf(rotate.y));
    tmp[10] = cosf(rotate.y) * cosf(rotate.x);

    matrix4x4Mul(matrix,tmp);
}

void matrix4x4SetTranslation(FIXED matrix[16], VECTOR trans) //이동
{
    matrix[3] = trans.x;
    matrix[7] = trans.y;
    matrix[11] = trans.z;
}









