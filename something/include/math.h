#include <tonc.h>

// #define PI_FLT 3.14159265f
#define TAU 0xFFFF
#define PI 0x8000 // round(TAU / 2)
#define ONE_DEGREE  0xB6
#define FIXED_12_SCALE (1 << 12)

typedef s32 FIXED_12;
typedef FIXED_12 ANGLE_FIXED_12;
typedef struct s_obj t_obj;


struct s_obj
{
    VECTOR vertex[512];
    int size;
};