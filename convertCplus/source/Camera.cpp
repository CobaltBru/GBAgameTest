#include "Camera.hpp"

void Camera::cameraInit(VECTOR pos,FIXED fov, FIXED near, FIXED far, int mode)
{

    int w, h;
    switch (mode) {
        case DCNT_MODE5:
            w = M5_WIDTH;
            h = M5_HEIGHT;
        break;
        case DCNT_MODE4:
            w = M4_WIDTH;
            h = M4_HEIGHT;
        break;
        default: 
            w = M5_WIDTH;
            h = M5_HEIGHT;
        break;
    }
    canvasWidth = int2fx(w);
    canvasHeight = int2fx(h);
    viewportWidth = float2fx(w / 100.f);
    viewportHeight = float2fx(h / 100.f);
    aspect = fxdiv(viewportWidth, viewportHeight);
    this->fov = fov;
    this->near = near;
    this->far = far;

    this->pos = pos;
    yaw = int2fx12(0);
    pitch = int2fx12(0);
    roll = int2fx12(0);
    lookAt = {0,0,1};
    matrix4x4setIdentity(world2cam);
    computePerspectiveMat();
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

void Camera::initWorldToCamspaceMat() //시점변환 행렬
{
    matrix4x4setIdentity(world2cam);
    VECTOR forward = vecUnit(vecSub(pos, lookAt));
    VECTOR tmp = {0,int2fx(1),0};
    VECTOR right; 
    VECTOR up;
    FIXED eps = 25; // Is about 0.009; assumes FIX_SHIFT == 8
    // TODO/FIXME: Handling of this special case (camera looking completely down/up) *does not work* at all for non-static scenes (interpolation is messed up).
    if (ABS(forward.x - tmp.x) < eps && ABS(forward.y - tmp.y) < eps && ABS(forward.z - tmp.z) < eps ) { // Special case where the camera looks straight up/down and the cross product "fails".
        right = vecUnit({forward.y, 0,0});
        up = vecUnit(vecCross(forward, right));
    } else {
        right = vecUnit(vecCross(tmp, forward));
        up = vecUnit(vecCross(forward, right));
    }
    matrix4x4SetBasis(world2cam, right, up, forward);

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

void Camera::computePerspectiveMat()
{
    FIXED near = near;
    FIXED far = far;
    FIXED top =  fxmul(float2fx(tan(fx2float(fov) / 2.0f )), near);
    FIXED bottom = -top;
    FIXED right = fxmul(top, aspect);
    FIXED left = -right;

    FIXED persp[16] = {
        fxdiv( fxmul(near, int2fx(2)), right - left), 0, fxdiv(right + left, right - left), 0,
        0, fxdiv(fxmul(near, int2fx(2)), top - bottom), fxdiv(top + bottom, top - bottom), 0,
        0, 0, -fxdiv(far + near, far - near), -fxdiv(fxmul(near, fxmul(int2fx(2), far)), far - near),
        0, 0, int2fx(-1), 0
    }; //4x4 투영변환행렬

    FIXED viewport2image[16] = {
        fxmul(aspect, fxmul(float2fx(0.5), fxdiv(canvasWidth, viewportWidth))), 0, 0,  fxdiv(canvasWidth, int2fx(2)), 
        0, -fxmul(float2fx(0.5), fxdiv(canvasHeight, viewportHeight)), 0, fxdiv(canvasHeight, int2fx(2)), 
        0, 0, int2fx(1), 0,
        0, 0, 0, int2fx(1)
    }; //하드웨어 종횡비 보정

    memcpy(perspMat, persp, sizeof(persp));
    memcpy(this->viewport2imageMat, viewport2image, sizeof(viewport2image));
}

FIXED* Camera::getPerspMat()
{
    return perspMat;
}
FIXED* Camera::getw2cMat()
{
    return world2cam;
}

void Camera::cameraRotateUP(ANGLE_FIXED_12 speed)
{
    pitch+=speed;
}
void Camera::cameraRotateDown(ANGLE_FIXED_12 speed)
{
    pitch-=speed;
}
void Camera::cameraRotateLeft(ANGLE_FIXED_12 speed)
{
    yaw+=speed;
}
void Camera::cameraRotateRight(ANGLE_FIXED_12 speed)
{
    yaw-=speed;
}
