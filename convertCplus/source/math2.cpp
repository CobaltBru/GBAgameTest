
#include "math2.hpp"
#include "util.hpp"

fixed getRadian(fixed num)
{
    return num * fixed(PI / 180.0f);
}

// void printMat(FIXED mat[16]);

vec3 vecCross(vec3 a, vec3 b)
{
    vec3 cross;
    cross.x = (a.y * b.z) - (a.z * b.y);
    cross.y = (a.z * b.x) - (a.x * b.z);
    cross.z = (a.x * b.y) - (a.y * b.x);
    return cross;
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

fixed   sqrt(fixed f) {
    fixed   l = 0;
    fixed   r = f + 1;
    fixed   m;

    while(l.num != r.num - 1) {
        m = (l + r) >> 1;
        if (m * m <= f)
            l = m;
        else
            r = m;
    }
    return (l);
}

fixed	abs(fixed f) {
    if (f > 0)
        return (f);
    return (-f);
}

vec2 sincos(int angle)
{
    angle = angle << 16 >> 16;
    int shift = (angle ^ (angle << 1)) & 0xC000;
    int x = (angle + shift) << 17 >> 17;
    fixed c = fixed::from((1 << FIX_SHIFT) - x * x / 882673);
    fixed s = sqrt(fixed(1) - c * c);

    if (shift & 0x4000)
        swap(c, s);
    if (angle < 0)
        s = -s;
    if (shift & 0x8000)
        c = -c;
    return {c, s};
}

fixed	dot(vec2 const &a, vec2 const &b) {
    return (a.x * b.x + a.y * b.y);
}

fixed	dot(vec3 const &a, vec3 const &b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}
fixed	dot(vec4 const &a, vec4 const &b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

vec3	cross(vec3 const &a, vec3 const &b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}

fixed	length(vec2 const &a) {
    return (sqrt(dot(a, a)));
}
fixed	length(vec3 const &a) {
    return (sqrt(dot(a, a)));
}
fixed	length(vec4 const &a) {
    return (sqrt(dot(a, a)));
}

vec2	normalize(vec2 const &a) {
    return (a / length(a));
}
vec3	normalize(vec3 const &a) {
    return (a / length(a));
}
vec4	normalize(vec4 const &a) {
    return (a / length(a));
}
