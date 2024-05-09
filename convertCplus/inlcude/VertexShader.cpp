#pragma once

#include "tonc.h"
#include "math.h"

class VertexShader
{
    FIXED Matrix[16];
public:
    void S_MatrixCalc(FIXED scale);
    void R_MatrixCalc(VECTOR rotate);
    void T_MatrixCalc(VECTOR trans);
    VECTOR vertexToWorld(VECTOR vertex);
};

VertexShader::VertexShader()
{
    matrix4x4setIdentity(Matrix);
}
void VertexShader::S_MatrixCalc(FIXED scale)
{
    matrix4x4scaler(Matrix,scale);
}

void VertexShader::R_MatrixCalc(VECTOR rotate)
{
    matrix4x4rotateYPR(Matrix, rotate);
}

void VertexShader::T_MatrixCalc(VECTOR trans)
{
    matrix4x4SetTranslation(Matrix, trans);
}

VECTOR VertexShader::vertexToWorld(VECTOR vertex)
{
    return vecTransformed(Matrix, vertex);
}