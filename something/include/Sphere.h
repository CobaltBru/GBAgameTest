#pragma once

#include <tonc.h>
#include "Hit.h"
#include "Ray.h"

typedef struct Sphere
{
    VECTOR centor;
    FIXED radius;
    VECTOR color;
}Sphere;

Hit IntersectRatCollision(Ray* ray)
{
    VECTOR VZERO = {0,0,0};
    Hit hit = {-1,VZERO,VZERO};

    FIXED b = 2 * vec_dot(ray->dir,())
}