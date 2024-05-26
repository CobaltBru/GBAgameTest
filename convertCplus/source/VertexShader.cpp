#include "VertexShader.hpp"

VertexShader::VertexShader()
{
    matrix = mat4::identity();
}

void VertexShader::TRS_MatrixCalc(vec3 scale, int yaw, int pitch, int roll, vec3 trans)
{
    // matrix = mat4::translate(trans.x, trans.y, trans.z) * matrix;
    mat4    T = mat4::translate(trans.x, trans.y, trans.z);
    mat4    R = mat4::rotateY(yaw) *  mat4::rotateX(pitch) * mat4::rotateZ(roll);
    mat4    S = mat4::scale(scale.x, scale.y, scale.z);
    // mat4    M = T * R * S; 
    this->matrix = T * R * S;
}

vec4 VertexShader::vertexToWorld(vec4 vertex)
{
    return matrix * vertex;
}

mat4 VertexShader::getMatrix()
{
    return matrix;
}