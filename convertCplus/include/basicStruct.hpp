#pragma once
#include <tonc.h>


typedef struct s_obj t_obj;

struct s_obj
{
    VECTOR vertex[512];
    int index[512];
    POINT rest[512];
    int v_size;
    int i_size;
};

