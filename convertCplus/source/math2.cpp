
#include <string.h>
#include <tonc.h>
#include <math.h>

#include "math2.h"


FIXED getRadian(FIXED num)
{
    return fxmul(num,fxdiv(PI,180.0f));
}

void printMat(FIXED mat[16]);

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

VECTOR vecScaled(VECTOR vec, FIXED factor) 
{
    vec.x = fxmul(vec.x, factor);
    vec.y = fxmul(vec.y, factor);
    vec.z = fxmul(vec.z, factor);
    return vec;
}

void vecScale(VECTOR *vec, FIXED factor) 
{
    vec->x = fxmul(vec->x, factor);
    vec->y = fxmul(vec->y, factor);
    vec->z = fxmul(vec->z, factor);
}

VECTOR vecAdd(VECTOR a, VECTOR b) 
{
    a.x = fxadd(a.x, b.x);
    a.y = fxadd(a.y, b.y);
    a.z = fxadd(a.z, b.z);
    return a;
}

VECTOR vecSub(VECTOR a, VECTOR b) 
{
    a.x = fxsub(a.x, b.x);
    a.y = fxsub(a.y, b.y);
    a.z = fxsub(a.z, b.z);
    return a;
}

VECTOR vecUnit(VECTOR a) 
{
    FIXED mag =  Sqrt((fxmul(a.x, a.x) + fxmul(a.y, a.y) + fxmul(a.z, a.z)) << (FIX_SHIFT) ); // sqrt(2**8) * sqrt(2**8) = 2**8
    return {fxdiv(a.x, mag), fxdiv(a.y, mag),fxdiv(a.z, mag) };
}

FIXED vecMag(VECTOR a) {
     return Sqrt((fxmul(a.x, a.x) + fxmul(a.y, a.y) + fxmul(a.z, a.z)) << (FIX_SHIFT) ); // sqrt(2**8) * sqrt(2**8) = 2**8
}


VECTOR vecCross(VECTOR a, VECTOR b) 
{
    VECTOR cross;
    cross.x = fxmul(a.y, b.z) - fxmul(a.z, b.y);
    cross.y = fxmul(a.z, b.x) - fxmul(a.x, b.z);
    cross.z = fxmul(a.x, b.y) - fxmul(a.y, b.x);
    return cross;
}

FIXED vecDot(VECTOR a, VECTOR b) 
{
    return fxmul(a.x, b.x) + fxmul(a.y, b.y) + fxmul(a.z, b.z);
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
void matrix4x4Transpose(FIXED mat[16]) 
{ // Useful, as the inversion of a square orthonormal matrix is equivalent to its transposition. We don't really need to invert other matrices so far. 
    FIXED tmp[16];
    memcpy(tmp, mat, sizeof(tmp[0]) * 16);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            matrix4x4Set(mat, row, col, matrix4x4Get(tmp, col, row));
        }
    }
}

void matrix4x4SetBasis(FIXED matrix[16], VECTOR x, VECTOR y, VECTOR z) 
{
    matrix[0] = x.x;
    matrix[1] = y.x;
    matrix[2] = z.x;

    matrix[4] = x.y;
    matrix[5] = y.y;
    matrix[6] = z.y;

    matrix[8] = x.z;
    matrix[9] = y.z;
    matrix[10] = z.z;
}
void matrix4x4setIdentity(FIXED matrix[16]) 
{
    memset(matrix, 0, sizeof(*matrix) * 16);
    matrix[0] = int2fx(1);
    matrix[5] = int2fx(1);
    matrix[10] = int2fx(1);
    matrix[15] = int2fx(1);
}

void matrix4x4scaler(FIXED matrix[16],FIXED scale) //확대축소
{
    matrix[0] = scale;
    matrix[5] = scale;
    matrix[10] = scale;
    //matrix[15] = scale;
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
void matrix4x4rotateYPR(FIXED matrix[16],ANGLE_FIXED_12 yaw, ANGLE_FIXED_12 pitch, ANGLE_FIXED_12 roll) //회전
{
    FIXED tmp[16];
    matrix4x4setIdentity(tmp);
    tmp[0] = fxmul(cosFx(roll), cosFx(yaw)) + fxmul(fxmul(sinFx(roll), sinFx(yaw)), sinFx(pitch));
    tmp[1] = -fxmul(sinFx(roll), cosFx(yaw)) + fxmul(fxmul(cosFx(roll), sinFx(yaw)), sinFx(pitch));
    tmp[2] = fxmul(sinFx(yaw), cosFx(pitch));
    // tmp[3] = 0;
    tmp[4] = fxmul(sinFx(roll), cosFx(pitch));
    tmp[5] = fxmul(cosFx(roll), cosFx(pitch));
    tmp[6] = -sinFx(pitch);
    // tmp[7] = 0;
    tmp[8] = fxmul(-cosFx(roll), sinFx(yaw)) + fxmul(fxmul(sinFx(roll), cosFx(yaw)), sinFx(pitch));
    tmp[9] = fxmul(sinFx(roll), sinFx(yaw)) + fxmul(fxmul(cosFx(roll), cosFx(yaw)), sinFx(pitch));
    tmp[10] = fxmul(cosFx(pitch), cosFx(yaw));
    matrix4x4Mul(matrix,tmp);
}

void matrix4x4SetTranslation(FIXED matrix[16], VECTOR trans) //이동
{
    matrix[3] = trans.x;
    matrix[7] = trans.y;
    matrix[11] = trans.z;
}









