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

fixed fixed::operator+(fixed other) const
{
    return num + other.num;
}
fixed fixed::operator-(fixed other) const
{
    return num - other.num;
}
fixed fixed::operator*(fixed other) const
{
    fixed tmp;
    tmp.num = int((i64(num) * other.num) >> FIX_SHIFT);
    return tmp;
}
fixed fixed::operator/(fixed other) const
{
    fixed tmp;
    tmp.num = int(((1 << FIX_SHIFT) * i64(num)) / other.num);
    return tmp;
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

