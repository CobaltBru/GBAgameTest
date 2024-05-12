
#include <tonc.h>
#include <math.h>
#include <string.h>
#include <tonc.h>
#include "math2.h"

class Camera
{
    VECTOR pos;
    ANGLE_FIXED_12 yaw,pitch,roll;
    VECTOR lookAt;
    FIXED perspMat[16];
    FIXED world2cam[16];
    FIXED tmpmat[16];

    FIXED canvasWidth,canvasHeight;
    FIXED viewportWidth, viewportHeight;
    FIXED aspect;
    FIXED fov, near, far;

    FIXED viewport2imageMat[16];


public:
    void cameraInit(VECTOR pos,FIXED fov, FIXED near, FIXED far, int mode);
    void cameraComputeRotMatrix(FIXED result[16]);
    void initWorldToCamspaceMat();
    void computePerspectiveMat();
    void cameraRotateUP(ANGLE_FIXED_12 speed);
    void cameraRotateDown(ANGLE_FIXED_12 speed);
    void cameraRotateLeft(ANGLE_FIXED_12 speed);
    void cameraRotateRight(ANGLE_FIXED_12 speed);
    FIXED* getPerspMat();
    FIXED* getw2cMat();
};
