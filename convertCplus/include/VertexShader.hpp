#include <tonc.h>
#include "math2.h"

class VertexShader
{
    FIXED Matrix[16];
public:
    VertexShader();
    void S_MatrixCalc(FIXED scale);
    void R_MatrixCalc(VECTOR rotate);
    void T_MatrixCalc(VECTOR trans);
    VECTOR vertexToWorld(VECTOR vertex);
};
