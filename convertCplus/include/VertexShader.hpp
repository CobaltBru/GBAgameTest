#pragma once
#include <tonc.h>
#include "math2.h"

class VertexShader
{
    FIXED Matrix[16];
public:
    VertexShader();
    void S_MatrixCalc(FIXED scale);
    void R_MatrixCalc(ANGLE_FIXED_12 yaw, ANGLE_FIXED_12 pitch, ANGLE_FIXED_12 roll);
    void T_MatrixCalc(VECTOR trans);
    VECTOR vertexToWorld(VECTOR vertex);
    FIXED* getMatrix();
};
