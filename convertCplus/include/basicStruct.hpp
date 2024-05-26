#include "math2.hpp"

typedef struct s_obj t_obj;

struct POINTS
{
    int x,y;
};

struct s_obj
{
    vec4 vertex[512];
    int index[512];
    POINTS rest[512];
    int v_size;
    int i_size;
};

