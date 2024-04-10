
#include <tonc.h>

typedef struct Circle
{
    VECTOR center;
    FIXED radius;
    FIXED radiusSquared;
    COLOR color;
}Circle;

bool IsInside(Circle* circle,VECTOR *p)
{
        VECTOR tmp;
        FIXED distanceSquared = vec_dot(vec_sub(&tmp,p,&circle->center), vec_sub(&tmp,p,&circle->center));
        if(distanceSquared <= circle->radiusSquared) return true;
        else return false;
}
