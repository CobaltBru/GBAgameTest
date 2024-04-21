#pragma once

#include <tonc.h>

typedef struct Triangle
{
    POINT a;
    POINT b;
    POINT c;
}Triangle;

void initTriangle(Triangle *self, POINT a, POINT b, POINT c)
{
    Triangle tmp = {a,b,c};
    POINT p_tmp={0,0};
    if(tmp.a.y>tmp.b.y)
    {
        p_tmp = tmp.b;
        tmp.b = tmp.a;
        tmp.a = p_tmp;
    }
    if(tmp.b.y>tmp.c.y)
    {
        p_tmp = tmp.c;
        tmp.c = tmp.b;
        tmp.b = p_tmp;
    }
    if(tmp.a.y>tmp.b.y)
    {
        p_tmp = tmp.b;
        tmp.b = tmp.a;
        tmp.a = p_tmp;
    }
    *self = tmp;
}