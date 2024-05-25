#pragma once
#include "math2.h"


class VertexShader
{
    mat4 matrix;
public:
    VertexShader();
    void S_MatrixCalc(fixed scale);
    void R_MatrixCalc(ANGLE_FIXED_12 yaw, ANGLE_FIXED_12 pitch, ANGLE_FIXED_12 roll);
    void T_MatrixCalc(vec4 trans);
    vec4 vertexToWorld(vec4 vertex);
    mat4 getMatrix();
};
