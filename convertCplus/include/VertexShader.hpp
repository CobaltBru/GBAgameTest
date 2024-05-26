#include "math2.hpp"

class VertexShader
{
    mat4 matrix;

public:
    VertexShader();
    void TRS_MatrixCalc(vec3 scale, int yaw, int pitch, int roll, vec3 trans);
    vec4 vertexToWorld(vec4 vertex);
    mat4 getMatrix();
};
