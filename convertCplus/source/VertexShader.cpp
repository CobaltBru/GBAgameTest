#include "VertexShader.hpp"

VertexShader::VertexShader()
{
    matrix = mat4::identity();
}
void VertexShader::S_MatrixCalc(fixed scale)
{
    matrix = matrix * scale;
}

void VertexShader::R_MatrixCalc(ANGLE_FIXED_12 yaw, ANGLE_FIXED_12 pitch, ANGLE_FIXED_12 roll)
{
    matrix4x4rotateYPR(matrix, yaw,pitch,roll);
}

void VertexShader::T_MatrixCalc(vec4 trans)
{
    matrix4x4SetTranslation(matrix, trans);
}

vec4 VertexShader::vertexToWorld(vec4 vertex)
{
    return matrix * vertex;
}

mat4 VertexShader::getMatrix()
{
    return matrix;
}