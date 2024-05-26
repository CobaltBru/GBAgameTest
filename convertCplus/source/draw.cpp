#include <tonc.h>
#include "math2.hpp"
#include "Camera.hpp"


void drawWireFrame(t_obj &obj, u32 mode) // 와이어 프레임
{
    for(int i = 0;i<obj.i_size;i+=3)
    {
        switch(mode)
        {
            case DCNT_MODE5:
                m5_line(obj.rest[i].x,obj.rest[i].y,obj.rest[i+1].x,obj.rest[i+1].y,CLR_WHITE);
                m5_line(obj.rest[i+1].x,obj.rest[i+1].y,obj.rest[i+2].x,obj.rest[i+2].y,CLR_WHITE);
                m5_line(obj.rest[i+2].x,obj.rest[i+2].y,obj.rest[i].x,obj.rest[i].y,CLR_WHITE);
                break;
            case DCNT_MODE4:
                m4_line(obj.rest[i].x,obj.rest[i].y,obj.rest[i+1].x,obj.rest[i+1].y,CLR_WHITE);
                m4_line(obj.rest[i+1].x,obj.rest[i+1].y,obj.rest[i+2].x,obj.rest[i+2].y,CLR_WHITE);
                m4_line(obj.rest[i+2].x,obj.rest[i+2].y,obj.rest[i].x,obj.rest[i].y,CLR_WHITE);
                break;
        }
    }
}

void printNrestOBJ(t_obj &obj) // 투영 전 오브젝트 출력
{
    for(int i = 0;i<obj.v_size;i++)
    {
        char s1[30];
        sprintf(s1,"(%g,%g,%g)\n",fx2float(obj.vertex[i].x),fx2float(obj.vertex[i].y),fx2float(obj.vertex[i].z));
        tte_write(s1);
    }
	tte_write("\n");
}

void printrestOBJ(t_obj &obj) // 투영 후 오브젝트 출력
{
    for(int i = 0;i<obj.v_size;i++)
    {
        char s1[30];
        sprintf(s1,"(%d,%d,%g)\n",obj.rest[i].x,obj.rest[i].y,fx2float(obj.vertex[i].z));
        tte_write(s1);
    }
	tte_write("\n");
}

void printMat(FIXED mat[16]) // 행렬 출력
{
    
    for(int i = 0;i<4;i++)
    {
        char s1[100];
        sprintf(s1,"[%g,%g,%g,%g]\n",fx2float(mat[(i*4)]),fx2float(mat[(i*4)+1]),fx2float(mat[(i*4)+2]),fx2float(mat[(i*4)+3]));
        tte_write(s1);
    }
    tte_write("\n");
}

void printVec(char* tag,VECTOR vec) // 벡터 출력
{
    char s1[100];
    sprintf(s1,"%s:(%g,%g,%g)\n",tag,fx2float(vec.x),fx2float(vec.y),fx2float(vec.z));
    tte_write(s1);
}

void printrestPoint(char* tag, int x, int y, FIXED z)
{
    char s1[100];
    sprintf(s1,"%s:(%d,%d,%g)\n",tag,x,y,fx2float(z));
    tte_write(s1);
}

void drawBefore(Camera& cam) //매 프레임마다  실행되어야함
{
    cam.initWorldToCamspaceMat(); // 시점변환 행렬 갱신
}