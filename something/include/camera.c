#pragma once

#include "math.h"



typedef struct Camera
{
    VECTOR pos;
    ANGLE_FIXED_12 yaw,pitch,roll;
    VECTOR lookAt;
    FIXED world2cam[16];
}Camera;

FIXED tmpmat[16];
void camera_init(Camera* cam, const VECTOR* pos, const VECTOR* dir)
{
    cam->pos = *pos;
    cam->yaw = int2fx12(0);
    cam->pitch = int2fx12(0);
    cam->roll = int2fx12(0);
    matrix4x4setIdentity(cam->world2cam);
    
}

static void cameraComputeRotMatrix(Camera *cam, FIXED result[16]) 
{
    // TODO: precompute yawPitchRollmatrix
    // ROTMAT =  yaw * pitch * roll
    matrix4x4createRotY(result, cam->yaw);
    matrix4x4createRotX(tmpmat, cam->pitch);
    matrix4x4Mul(result, tmpmat);
    matrix4x4createRotZ(tmpmat, cam->roll);
    matrix4x4Mul(result, tmpmat);
}

void WorldToCamspace(Camera *cam)
{
    FIXED rotmat[16];
    cameraComputeRotMatrix(cam, rotmat);
    matrix4x4Mul(cam->world2cam, rotmat);

    // Invert the matrix so we get the world-to-camera matrix from our current camera-to-world matrix. 
    // (The transposition of square orthonormal matrices is equivalent to their inversion. If something goes wrong, our matrix is not orthonormal; try the numerical solution.)
    matrix4x4Transpose(cam->world2cam); 

    // Compute translation matrix and put it into 'transMat'.
    FIXED transMat[16];
    matrix4x4setIdentity(transMat);
    matrix4x4SetTranslation(transMat, (VECTOR){.x=-cam->pos.x, .y=-cam->pos.y, .z=-cam->pos.z} ); 

    // Post-multiply the translation matrix with the rotation matrix.
    matrix4x4Mul(cam->world2cam, transMat); // world2cam' = world2cam  * transMat 
}