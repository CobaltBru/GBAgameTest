#pragma once
#include "math2.h"

typedef struct s_obj t_obj;

struct POINT
{
    int x,y;
};

struct s_obj
{
    vec4 vertex[512];
    int index[512];
    POINT rest[512];
    int v_size;
    int i_size;
};

