#include <tonc.h>
#include "math2.h"

void drawWireFrame(t_obj &obj, int mode)
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