#pragma once

#include "math.h"

class Camera
{
    VECTOR pos;
    ANGLE_FIXED_12 yaw,pitch,roll;
    VECTOR lookAt;
    FIXED world2cam[16];
    FIXED tmpmat[16];
public:
    void cameraInit(const VECTOR* pos, const VECTOR* dir);
    void cameraComputeRotMatrix(FIXED result[16]);
    void worldToCamspace();
};

void Camera::cameraInit(const VECTOR* pos, const VECTOR* dir)
{
    this->pos = *pos;
    yaw = int2fx12(0);
    pitch = int2fx12(0);
    roll = int2fx12(0);
    matrix4x4setIdentity(world2cam);
}

void Camera::cameraComputeRotMatrix(FIXED result[16]) 
{
    // TODO: precompute yawPitchRollmatrix
    // ROTMAT =  yaw * pitch * roll
    matrix4x4createRotY(result, yaw);
    matrix4x4createRotX(tmpmat, pitch);
    matrix4x4Mul(result, tmpmat);
    matrix4x4createRotZ(tmpmat, roll);
    matrix4x4Mul(result, tmpmat);
}

void Camera::worldToCamspace()
{
    FIXED rotmat[16];
    cameraComputeRotMatrix(rotmat);
    matrix4x4Mul(world2cam, rotmat);

    // Invert the matrix so we get the world-to-camera matrix from our current camera-to-world matrix. 
    // (The transposition of square orthonormal matrices is equivalent to their inversion. If something goes wrong, our matrix is not orthonormal; try the numerical solution.)
    matrix4x4Transpose(world2cam); 

    // Compute translation matrix and put it into 'transMat'.
    FIXED transMat[16];
    matrix4x4setIdentity(transMat);
    matrix4x4SetTranslation(transMat, {-pos.x,-pos.y,-pos.z} ); 

    // Post-multiply the translation matrix with the rotation matrix.
    matrix4x4Mul(world2cam, transMat); // world2cam' = world2cam  * transMat 
}