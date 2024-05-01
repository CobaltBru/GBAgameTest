#include <tonc.h>
#include "./math.h"
#include "../include/triangle.h"

typedef struct object
{
    Vec3 vertex[512];
    int size;
} OBJ;

FIXED *S_matrix_init(Vec3 scale) // Size mat
{
    FIXED matrix[16];
    matrix4x4setIdentity(matrix);
    matrix[0] = fxmul(matrix[0], scale.x);
    matrix[5] = fxmul(matrix[5], scale.y);
    matrix[10] = fxmul(matrix[10], scale.z);
    return matrix;
}
FIXED *R_matrix_init(Vec3 rotate) // Rotate mat
{
    FIXED matrix[16];
    matrix4x4createYawPitchRoll(matrix, rotate.z, rotate.y, rotate.x);
    return matrix;
}

FIXED *T_matrix_init(Vec3 trans)
{
    FIXED matrix[16];
    matrix4x4SetTranslation(matrix, trans);
    return matrix;
}

void vec_world_transform(OBJ *obj, Vec3 scale, Vec3 rotate, Vec3 trans)
{
    FIXED S_matrix[16];
    memcpy16(S_matrix, S_matrix_init(scale),sizeof(S_matrix));
    FIXED R_matrix[16];
    memcpy16(R_matrix, R_matrix_init(rotate),sizeof(R_matrix));
    FIXED T_matrix[16];
    memcpy16(T_matrix, T_matrix_init(trans),sizeof(T_matrix));
    FIXED W_matrix[16] = matrix4x4Mul(matrix4x4Mul(S_matrix,R_matrix), T_matrix);
    for (int i = 0; i < obj->size; i++)
    {
        obj->vertex[i] = vecTransformed(W_matrix, obj->vertex[i]);
    }
}