#include <stdio.h>
#include <tonc.h>
#include <math.h>
#include "math2.h"
#include "Camera.hpp"
#include "VertexShader.hpp"
// #include "draw.cpp"
//  #include "VertexShader.cpp"
//  #include "Camera.cpp"
void drawBefore(Camera& cam);
void drawWireFrame(t_obj &obj, u32 mode);
void printOBJ(t_obj &obj);
void printMat(FIXED mat[16]);
void printVec(char* tag,VECTOR vec);

void setMode0() {
    // 화면 모드 0 및 BG0 활성화
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    
    // BG0 컨트롤 설정 (16컬러 타일, 1번 캐릭터 블록, 31번 스크린 블록)
    tte_init_se_default(0, BG_CBB(0)|BG_SBB(31));

}

void setMode4() {
    REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	m4_fill(BLD_BLACK);
}

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	setMode0();
	
	t_obj obj;//--------------------------------obj init
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
	//printOBJ(obj);

	VertexShader v;//-----------------------vertexShader apply
	v.S_MatrixCalc(int2fx(20));
	v.R_MatrixCalc(int2fx(0), int2fx(0), int2fx(0));
	v.T_MatrixCalc({int2fx(50), int2fx(50), int2fx(50)});
	//printMat(v.getMatrix());
	for (int i = 0; i < obj.v_size; i++)
	{
		obj.vertex[i] = v.vertexToWorld(obj.vertex[i]);
	}
	//printOBJ(obj);

	Camera cam; //------------------camera setting
	cam.cameraInit({int2fx(50), int2fx(50), int2fx(-10)}, 192, int2fx(1), int2fx(256), DCNT_MODE4);
	cam.setLookAt({int2fx(0),int2fx(0),int2fx(10)});
	//printMat(cam.getPerspMat());
	drawBefore(cam); //시점 변환 행렬 초기화
	//printMat(cam.getw2cMat());
	//printOBJ(obj);
	cam.applyMatrix(obj);

	//drawWireFrame(obj, DCNT_MODE4);
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
