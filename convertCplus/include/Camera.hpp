#pragma once
#include <tonc.h>
#include <math.h>
#include <string.h>
#include <tonc.h>
#include "math2.h"
#include "basicStruct.hpp"

class Camera
{
    public:
    vec3 pos; //카메라 위치
    ANGLE_FIXED_12 yaw,pitch,roll; //카메라 회전
    vec3 lookAt; // 카메라 시선 방향
    mat4 perspMat; //투영변환 행렬
    mat4 world2cam; // 카메라시점 변환 행렬
    mat4 tmpmat; //변환을 위한 임시 행렬

    fixed canvasWidth,canvasHeight; //캔버스 크기
    fixed viewportWidth, viewportHeight; // 뷰포트 크기
    fixed aspect; //화면 비율
    fixed fov, near, far; //시야각, 절두체 앞 뒤

    mat4 viewport2imageMat[16]; // 클립->실제 화면 변환 행렬

    fixed perspFacX;
    fixed perspFacY;
    fixed viewportTransFacX;
    fixed viewportTransAddX;
    fixed viewportTransFacY;
    fixed viewportTransAddY;


public:
    void cameraInit(vec3 pos,fixed fov, fixed near, fixed far, int mode);
    void cameraComputeRotMatrix(mat4 &result); //카메라 회전 계산
    void initWorldToCamspaceMat(); //카메라 시점 변환 행렬 계산
    void computePerspectiveMat(); //투영변환 뷰포트변환 행렬 계산
    void cameraRotateUP(ANGLE_FIXED_12 speed);
    void cameraRotateDown(ANGLE_FIXED_12 speed);
    void cameraRotateLeft(ANGLE_FIXED_12 speed);
    void cameraRotateRight(ANGLE_FIXED_12 speed);
    void applyMatrix(t_obj& obj); //월드좌표를 ndc로 변환 후 투영후 뷰포트 변환
    mat4 getPerspMat();
    mat4 getw2cMat();
    mat4 getv2iMat();
    void setLookAt(vec3 dir);
};
