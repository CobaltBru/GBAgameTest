
#include "math2.hpp"
#include "util.hpp"

fixed getRadian(fixed num)
{
    return num * fixed(PI / 180.0f);
}

//void printMat(FIXED mat[16]);


vec3 vecCross(vec3 a, vec3 b) 
{
    vec3 cross;
    cross.x = (a.y * b.z) - (a.z * b.y);
    cross.y = (a.z * b.x) - (a.x * b.z);
    cross.z = (a.x * b.y) - (a.y * b.x);
    return cross;
}
fixed ABS(fixed number)
{
    return number > fixed(0) ? number : -number;
}

// void matrix4x4SetBasis(FIXED matrix[16], VECTOR x, VECTOR y, VECTOR z) 
// {
//     matrix[0] = x.x;
//     matrix[1] = y.x;
//     matrix[2] = z.x;

//     matrix[4] = x.y;
//     matrix[5] = y.y;
//     matrix[6] = z.y;

//     matrix[8] = x.z;
//     matrix[9] = y.z;
//     matrix[10] = z.z;
// }


mat4 matrix4x4createRotX(int angle) 
{
    mat4 matrix = mat4::identity();
    // x y z tx
    // x y z ty
    // x y z tz
    // 0 0 0 w
    // y-basis
    fixed sine;
    fixed cosine;
    sincos(angle,sine,cosine);

    matrix.element[5] = cosine;
    matrix.element[9] = sine; // minus
    // z-basis
    matrix.element[6] = -sine; // plus
    matrix.element[10] = cosine;
    return matrix;
}

mat4 matrix4x4createRotY(int angle) 
{
    mat4 matrix = mat4::identity();

    fixed sine;
    fixed cosine;
    sincos(angle,sine,cosine);
    // x-basis
    matrix.element[0] = cosine;
    matrix.element[8] = -sine;
    // z-basis
    matrix.element[2] = sine;
    matrix.element[10] = cosine;
    return matrix;
}

mat4 matrix4x4createRotZ(int angle) 
{
    mat4 matrix = mat4::identity();

    fixed sine;
    fixed cosine;
    sincos(angle,sine,cosine);
    // x-basis
    matrix.element[0] = cosine;
    matrix.element[4] = sine;
    // y-basis
    matrix.element[1] = -sine;
    matrix.element[5] = cosine;
    return matrix;
}
void matrix4x4rotateYPR(mat4 &matrix,int yaw, int pitch, int roll) //회전
{
    mat4 tmp = mat4::identity();
    tmp.element[0] = fxmul(cosFx(roll), cosFx(yaw)) + fxmul(fxmul(sinFx(roll), sinFx(yaw)), sinFx(pitch));
    tmp.element[1] = -fxmul(sinFx(roll), cosFx(yaw)) + fxmul(fxmul(cosFx(roll), sinFx(yaw)), sinFx(pitch));
    tmp.element[2] = fxmul(sinFx(yaw), cosFx(pitch));
    // tmp[3] = 0;
    tmp.element[4] = fxmul(sinFx(roll), cosFx(pitch));
    tmp.element[5] = fxmul(cosFx(roll), cosFx(pitch));
    tmp.element[6] = -sinFx(pitch);
    // tmp[7] = 0;
    tmp.element[8] = fxmul(-cosFx(roll), sinFx(yaw)) + fxmul(fxmul(sinFx(roll), cosFx(yaw)), sinFx(pitch));
    tmp.element[9] = fxmul(sinFx(roll), sinFx(yaw)) + fxmul(fxmul(cosFx(roll), cosFx(yaw)), sinFx(pitch));
    tmp.element[10] = fxmul(cosFx(pitch), cosFx(yaw));
    matrix = matrix * tmp;
}

void matrix4x4SetTranslation(mat4 &matrix, vec4 trans) //이동
{
    matrix.element[3] = trans.x;
    matrix.element[7] = trans.y;
    matrix.element[11] = trans.z;
}

void    sincos(int angle, fixed &sine, fixed &cosine) {
    int     shift = (angle ^ (angle << 1)) & 0xC000;
    int     x = (angle + shift) << 17 >> 17;
    fixed   c = fixed::from((1 << FIX_SHIFT) - x * x / 882669);
    fixed   s = fixed::sqrt(fixed(1) - c * c);

    if (shift & 0x4000)
        swap(c, s);
    if (angle < 0)
        s = -s;
    if (shift & 0x8000)
        c = -c;
    sine = s;
    cosine = c;
}
