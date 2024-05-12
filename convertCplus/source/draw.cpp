#include <tonc.h>
#include "math2.h"

void drawWireFrame(t_obj &obj, u32 mode)
{
    for(int i = 0;i<obj.i_size;i+=3)
    {
        switch(mode)
        {
            case DCNT_MODE5:
                m5_line(obj.vertex[i].x,obj.vertex[i].y,obj.vertex[i+1].x,obj.vertex[i+1].y,CLR_WHITE);
                m5_line(obj.vertex[i+1].x,obj.vertex[i+1].y,obj.vertex[i+2].x,obj.vertex[i+2].y,CLR_WHITE);
                m5_line(obj.vertex[i+2].x,obj.vertex[i+2].y,obj.vertex[i].x,obj.vertex[i].y,CLR_WHITE);
                break;
            case DCNT_MODE4:
                m4_line(obj.vertex[i].x,obj.vertex[i].y,obj.vertex[i+1].x,obj.vertex[i+1].y,CLR_WHITE);
                m4_line(obj.vertex[i+1].x,obj.vertex[i+1].y,obj.vertex[i+2].x,obj.vertex[i+2].y,CLR_WHITE);
                m4_line(obj.vertex[i+2].x,obj.vertex[i+2].y,obj.vertex[i].x,obj.vertex[i].y,CLR_WHITE);
                break;
        }
    }
}

void printOBJ(t_obj &obj)
{
    for(int i = 0;i<obj.v_size;i++)
    {
        char s1[30];
        sprintf(s1,"(%g,%g,%g)\n",fx2float(obj.vertex[i].x),fx2float(obj.vertex[i].y),fx2float(obj.vertex[i].z));
        tte_write(s1);
    }
	tte_write("\n");
}

void printMat(FIXED mat[16])
{
    
    for(int i = 0;i<4;i++)
    {
        char s1[100];
        sprintf(s1,"[%g,%g,%g,%g]\n",fx2float(mat[(i*4)]),fx2float(mat[(i*4)+1]),fx2float(mat[(i*4)+2]),fx2float(mat[(i*4)+3]));
        tte_write(s1);
    }
    tte_write("\n");
}