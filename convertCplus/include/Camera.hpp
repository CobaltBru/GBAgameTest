#include <math.h>
#include <string.h>
#include "math2.hpp"
#include "basicStruct.hpp"

#define DCNT_MODE0				 0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-3: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap

#define DCNT_BG0			0x0100	//!< Enable bg 0
#define DCNT_BG1			0x0200	//!< Enable bg 1
#define DCNT_BG2			0x0400	//!< Enable bg 2
#define DCNT_BG3			0x0800	//!< Enable bg 3

#define SCREEN_WIDTH		240
#define SCREEN_HEIGHT		160

#define M3_WIDTH			SCREEN_WIDTH
#define M3_HEIGHT			SCREEN_HEIGHT
#define M4_WIDTH			SCREEN_WIDTH
#define M4_HEIGHT			SCREEN_HEIGHT
#define M5_WIDTH			160
#define M5_HEIGHT			128

class Camera
{
    public:
    vec3 pos; //카메라 위치
    int yaw,pitch,roll; //카메라 회전
    vec3 lookAt; // 카메라 시선 방향
    mat4 perspMat; //투영변환 행렬
    mat4 world2cam; // 카메라시점 변환 행렬

    fixed canvasWidth,canvasHeight; //캔버스 크기
    fixed aspect; //화면 비율
    fixed fov, near, far; //시야각, 절두체 앞 뒤



public:
    void cameraInit(vec3 pos,fixed fov, fixed near, fixed far, int mode);
    void cameraComputeRotMatrix(mat4 &result); //카메라 회전 계산
    void initWorldToCamspaceMat(); //카메라 시점 변환 행렬 계산
    void computePerspectiveMat(); //투영변환 뷰포트변환 행렬 계산
    void cameraRotateUP(int speed);
    void cameraRotateDown(int speed);
    void cameraRotateLeft(int speed);
    void cameraRotateRight(int speed);
    void applyMatrix(t_obj& obj); //월드좌표를 ndc로 변환 후 투영후 뷰포트 변환
    mat4 getPerspMat();
    mat4 getw2cMat();
    void setLookAt(vec3 dir);
};
