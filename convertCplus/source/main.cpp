#include <stdio.h>
#include <tonc.h>
#include <math.h>
#include "math2.h"
#include "Camera.hpp"
#include "VertexShader.hpp"
// #include "draw.cpp"
// #include "VertexShader.cpp"
// #include "Camera.cpp"


void drawWireFrame(t_obj &obj, int mode);

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	// Video mode 0, enable bg 0.
	REG_DISPCNT= DCNT_MODE4 | DCNT_BG2;
	m4_fill(CLR_BLACK);

	t_obj obj;
	VECTOR vertex[] = {{0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1}};
	memcpy(obj.vertex,vertex,sizeof(vertex));
	int idx[]={0,1,2,2,1,3,0,4,1,1,4,5,3,1,5,3,5,7,7,5,4,7,4,6,6,4,0,6,0,2,0,4,1,1,4,5,2,6,3,3,6,7};
	memcpy(obj.index,idx,sizeof(idx));
	obj.v_size = 8;
	obj.i_size = 42;

	VertexShader v;
	v.S_MatrixCalc(10);
	v.R_MatrixCalc({0,0,0});
	v.T_MatrixCalc({10,50,50});
	for(int i =0;i<obj.v_size;i++)
	{
		obj.vertex[i] = v.vertexToWorld(obj.vertex[i]);
	}
	Camera cam;
	cam.cameraInit({0,0,-10},90,5,100,DCNT_MODE4);
	drawWireFrame(obj,DCNT_MODE4);
	while(1)
	{
		
	}

	return 0;
}
