#include "math2.hpp"
#include "Camera.hpp"
#include <tonc.h>

void drawWireFrame(t_obj &obj, int mode) // 와이어 프레임
{
    for (int i = 0; i < obj.i_size; i += 3)
    {
        int idx1 = obj.index[i];
        int idx2 = obj.index[i + 1];
        int idx3 = obj.index[i + 2];
        switch (mode)
        {
        case DCNT_MODE5:
            m5_line(obj.rest[idx1].x, obj.rest[idx1].y, obj.rest[idx2].x, obj.rest[idx2].y, CLR_WHITE);
            m5_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx3].x, obj.rest[idx3].y, CLR_WHITE);
            m5_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx1].x, obj.rest[idx1].y, CLR_WHITE);
            break;
        case DCNT_MODE4:
            m3_line(obj.rest[idx1].x, obj.rest[idx1].y, obj.rest[idx2].x, obj.rest[idx2].y, CLR_WHITE);
            m3_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx3].x, obj.rest[idx3].y, CLR_WHITE);
            m3_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx1].x, obj.rest[idx1].y, CLR_WHITE);
            break;
        default:
            m3_line(obj.rest[idx1].x, obj.rest[idx1].y, obj.rest[idx2].x, obj.rest[idx2].y, CLR_WHITE);
            m3_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx3].x, obj.rest[idx3].y, CLR_WHITE);
            m3_line(obj.rest[idx2].x, obj.rest[idx2].y, obj.rest[idx1].x, obj.rest[idx1].y, CLR_WHITE);
            break;
        }
    }
}

void printNrestOBJ(t_obj &obj) // 투영 전 오브젝트 출력
{
    for (int i = 0; i < obj.v_size; i++)
    {
        char s1[30];
        sprintf(s1, "(%g,%g,%g,%g)\n", float(obj.vertex[i].x), float(obj.vertex[i].y),
                float(obj.vertex[i].z), float(obj.vertex[i].w));
        tte_write(s1);
    }
    tte_write("\n");
}

void printrestOBJ(t_obj &obj) // 투영 후 오브젝트 출력
{
    for (int i = 0; i < obj.v_size; i++)
    {
        char s1[30];
        sprintf(s1, "(%d,%d,%g)\n", obj.rest[i].x, obj.rest[i].y, float(obj.vertex[i].z));
        tte_write(s1);
    }
    tte_write("\n");
}

void printMat(mat4 mat) // 행렬 출력
{

    for (int i = 0; i < 4; i++)
    {
        char s1[100];
        sprintf(s1, "[%g,%g,%g,%g]\n", float(mat.element[(i * 4)]), float(mat.element[(i * 4) + 1]), float(mat.element[(i * 4) + 2]), float(mat.element[(i * 4) + 3]));
        tte_write(s1);
    }
    tte_write("\n");
}

void printVec(char *tag, vec2 vec) // 벡터 출력
{
    char s1[100];
    sprintf(s1, "%s:(%g,%g)\n", tag, float(vec.x), float(vec.y));
    tte_write(s1);
}

void printVec(char *tag, vec3 vec) // 벡터 출력
{
    char s1[100];
    sprintf(s1, "%s:(%g,%g,%g)\n", tag, float(vec.x), float(vec.y), float(vec.z));
    tte_write(s1);
}

void printVec(char *tag, vec4 vec) // 벡터 출력
{
    char s1[100];
    sprintf(s1, "%s:(%g,%g,%g,%g)\n", tag, float(vec.x), float(vec.y), float(vec.z), float(vec.w));
    tte_write(s1);
}

void printrestPoint(char *tag, int x, int y, fixed z)
{
    char s1[100];
    sprintf(s1, "%s:(%d,%d,%g)\n", tag, x, y, float(z));
    tte_write(s1);
}

void drawBefore(Camera &cam) // 매 프레임마다  실행되어야함
{
    cam.initWorldToCamspaceMat(); // 시점변환 행렬 갱신
}