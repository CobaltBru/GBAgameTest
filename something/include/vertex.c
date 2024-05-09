#pragma once

#include "math.c"

void S_matrix_init(float matrix[16],VECTOR scale)
{
    matrix4x4scaler(matrix,scale);
}

void R_matrix_init(float matrix[16], VECTOR rotate)
{
    matrix4x4rotateYPR(matrix, rotate);
}

void T_matrix_init(float matrix[16], VECTOR trans)
{
    matrix4x4SetTranslation(matrix,trans);
}

void vertex_to_world(VECTOR* vertex, const VECTOR *scale, const VECTOR *rotate, const VECTOR *trans)
{
    float matrix[16];
    matrix4x4setIdentity(matrix);
    matrix4x4scaler(matrix, *scale);
    matrix4x4rotateYPR(matrix, *rotate);
    matrix4x4SetTranslation(matrix, *trans);

    vecTransform(matrix,vertex);
}