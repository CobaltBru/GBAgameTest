
#include <iostream>
#include <cmath>
#include "fixed.hpp"
#include "vec2.hpp"
#include "util.hpp"

fixed   sqrt(fixed f) {
    fixed   l = 0;
    fixed   r = f + fixed::from(1);
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

vec2    ref_sincos(int angle) {
    double da = angle * 3.141592 / 32767;
    return {float(cos(da)), float(sin(da))};
}

int main(void) {

    for (int i = 0; i < 32767; i += 100) {
        vec2    b = sincos(i);
        vec2    c = ref_sincos(i);
        std::cout << float(b.x) << " ,, " << float(c.x) << std::endl;
    }
}
