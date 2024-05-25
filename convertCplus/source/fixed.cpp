#include "fixed.hpp"

typedef long long i64;

fixed::fixed() {}

fixed::fixed(int d)
{
    num = d << FIX_SHIFT;
}

fixed::fixed(float f)
{
    num = f * (1 << FIX_SHIFT);
}
fixed::operator    float() const
{
    return num / (1 << FIX_SHIFT);
}
fixed::operator    int() const
{
    return num >> FIX_SHIFT;
}

fixed   fixed::operator-() const {
    return fixed::from(this->num);
}

fixed fixed::operator+(fixed other) const
{
    return fixed::from(num + other.num);
}
fixed fixed::operator-(fixed other) const
{
    return fixed::from(num - other.num);
}
fixed fixed::operator*(fixed other) const
{
    return fixed::from(int((i64(num) * other.num) >> FIX_SHIFT));
}
fixed fixed::operator/(fixed other) const
{
    return fixed::from(int(((1 << FIX_SHIFT) * i64(num)) / other.num));
}

bool fixed::operator<(fixed other) const {
    return (this->num < other.num);
}

bool fixed::operator>(fixed other) const {
    return (this->num > other.num);
}

bool fixed::operator<=(fixed other) const {
    return (this->num <= other.num);
}

bool fixed::operator>=(fixed other) const {
    return (this->num >= other.num);
}

bool fixed::operator==(fixed other) const {
    return (this->num == other.num);
}

bool fixed::operator!=(fixed other) const {
    return (this->num != other.num);
}


fixed &fixed::operator+=(fixed other) {
    this->num += other.num;
    return (*this);
}

fixed &fixed::operator-=(fixed other) {
    this->num -= other.num;
    return (*this);
}

fixed &fixed::operator*=(fixed other) {
    *this = *this * other;
    return (*this);
}

fixed &fixed::operator/=(fixed other) {
    *this = *this / other;
    return (*this);
}

fixed   fixed::sqrt(fixed other) {
    int     value = 0;

    for (int i = 15; i >= 0; --i) {
        int const   width = 1 << i;
        int const   prediction = (value + width) * (value + width);
    
        if (prediction <= (other.num << FIX_SHIFT))
            value += width;
    }
    return (fixed::from(value));
}

fixed   fixed::from(int i) {
    fixed   ret;

    ret.num = i;
    return (ret);
}

