#include <stdio.h>
#include <tonc.h>
#include <math.h>
#include "math2.h"
#include "Camera.hpp"
#include "VertexShader.hpp"
// #include "draw.cpp"
//  #include "VertexShader.cpp"
//  #include "Camera.cpp"

void drawWireFrame(t_obj &obj, int mode);
void printOBJ(t_obj &obj);
void printMat(FIXED mat[16]);

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	// Video mode 0, enable bg 0.
	// REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	// m0_fill(CLR_BLACK);
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
	t_obj obj;
	VECTOR vertex[] =
		{{int2fx(0), int2fx(0), int2fx(0)},
		 {int2fx(1), int2fx(0), int2fx(0)},
		 {int2fx(0), int2fx(1), int2fx(0)},
		 {int2fx(1), int2fx(1), int2fx(0)},
		 {int2fx(0), int2fx(0), int2fx(1)},
		 {int2fx(1), int2fx(0), int2fx(1)},
		 {int2fx(0), int2fx(1), int2fx(1)},
		 {int2fx(1), int2fx(1), int2fx(1)}};
	memcpy(obj.vertex, vertex, sizeof(vertex));
	int idx[] = {0, 1, 2, 2, 1, 3, 0, 4, 1, 1, 4, 5, 3, 1, 5, 3, 5, 7, 7, 5, 4, 7, 4, 6, 6, 4, 0, 6, 0, 2, 0, 4, 1, 1, 4, 5, 2, 6, 3, 3, 6, 7};
	memcpy(obj.index, idx, sizeof(idx));
	obj.v_size = 8;
	obj.i_size = 42;
	// printOBJ(obj);

	VertexShader v;
	v.S_MatrixCalc(int2fx(10));
	v.R_MatrixCalc(int2fx(0), int2fx(0), int2fx(0));
	v.T_MatrixCalc({int2fx(10), int2fx(50), int2fx(50)});
	// printMat(v.getMatrix());
	for (int i = 0; i < obj.v_size; i++)
	{
		obj.vertex[i] = v.vertexToWorld(obj.vertex[i]);
		// printOBJ(obj);
	}
	Camera cam;
	cam.cameraInit({int2fx(0), int2fx(0), int2fx(0)}, int2fx(192), int2fx(1), int2fx(256), DCNT_MODE4);
	printMat(cam.getPerspMat());
	// drawWireFrame(obj, DCNT_MODE4);
	cam.initWorldToCamspaceMat();
	//printMat(cam.getPerspMat());
	for (int i = 0; i < obj.v_size; i++)
	{
		obj.vertex[i] = vecTransformed(cam.getw2cMat(), obj.vertex[i]);
	}
	printOBJ(obj);

	// while (1)
	// {
	// 	vid_vsync();
	// 	key_poll();
	// 	if (key_hit(KEY_UP))
	// 		cam.cameraRotateUP(1);
	// 	if (key_hit(KEY_DOWN))
	// 		cam.cameraRotateDown(1);
	// 	if (key_hit(KEY_LEFT))
	// 		cam.cameraRotateLeft(1);
	// 	if (key_hit(KEY_RIGHT))
	// 		cam.cameraRotateRight(1);

	// }

	return 0;
}
