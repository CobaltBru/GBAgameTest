#include <stdio.h>
#include <math.h>
#include "math2.hpp"
#include "Camera.hpp"
#include "VertexShader.hpp"

#include <tonc.h>
// #include "draw.cpp"
//  #include "VertexShader.cpp"
//  #include "Camera.cpp"
void drawBefore(Camera &cam);
void drawWireFrame(t_obj &obj, int mode);
void printNrestOBJ(t_obj &obj);
void printrestOBJ(t_obj &obj);
void printMat(mat4 mat);
void printVec(char *tag, vec2 vec);
void printVec(char *tag, vec3 vec);
void printVec(char *tag, vec4 vec);

void setMode0()
{
	// 화면 모드 0 및 BG0 활성화
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	// BG0 컨트롤 설정 (16컬러 타일, 1번 캐릭터 블록, 31번 스크린 블록)
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
}

void setMode4()
{
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	pal_bg_mem[0] = CLR_BLACK;
	pal_bg_mem[1] = CLR_WHITE;

	m4_fill(0);
	//vid_flip();

}

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	setMode4();
	
	t_obj obj,runtime_obj;		//--------------------------------obj init
	vec4 vertex[] = 
		{{0, 0, 0, 1},
		 {1, 0, 0, 1},
		 {0, 1, 0, 1},
		 {1, 1, 0, 1},
		 {0, 0, 1, 1},
		 {1, 0, 1, 1},
		 {0, 1, 1, 1},
		 {1, 1, 1, 1}};
	memcpy(obj.vertex, vertex, sizeof(vertex));
	int idx[] = {0, 1, 2, 2, 1, 3, 0, 4, 1, 1, 4, 5, 3, 1, 5, 3, 5, 7, 7, 5, 4, 7, 4, 6, 6, 4, 0, 6, 0, 2, 6, 2, 3, 6, 3, 7};
	memcpy(obj.index, idx, sizeof(idx));
	obj.v_size = 8;
	obj.i_size = 36;
	//printNrestOBJ(obj);
	runtime_obj = obj;
	VertexShader v; //-----------------------vertexShader apply
	int yaw = 0,pitch = 0, roll=0;
	v.TRS_MatrixCalc({10,10,10},yaw,pitch,roll,{50,50,50});
	// printMat(v.getMatrix());
	for (int i = 0; i < runtime_obj.v_size; i++)
	{
		runtime_obj.vertex[i] = v.vertexToWorld(obj.vertex[i]);
	}
	//printNrestOBJ(obj);

	Camera cam; //------------------camera setting
	cam.cameraInit({50, 50, -10}, 3.141592f / 3, 1, 256, DCNT_MODE4);
	cam.setLookAt({50, 50, 10}); // 이거 되나?
	drawBefore(cam); // 시점 변환 행렬 초기화
	// printMat(cam.getw2cMat());
	// printOBJ(obj);
	
	cam.applyMatrix(runtime_obj);
	drawWireFrame(runtime_obj, DCNT_MODE4);
	//printrestOBJ(obj);

	while (1)
	{
		vid_vsync();
		key_poll();
		m4_fill(0);
		runtime_obj = obj;
		pitch+= 1000 * key_tri_vert();
		yaw+= 1000 * key_tri_horz();

		v.TRS_MatrixCalc({10,10,10},yaw,pitch,roll,{50,50,50});
		for (int i = 0; i < runtime_obj.v_size; i++)
			{
				runtime_obj.vertex[i] = v.vertexToWorld(runtime_obj.vertex[i]);
			}
		drawBefore(cam);
		cam.applyMatrix(runtime_obj);
		drawWireFrame(runtime_obj, DCNT_MODE4);
		//m4_fill(CLR_RED);

		VBlankIntrWait();
		vid_flip();
		
		
	}
	return 0;
}
