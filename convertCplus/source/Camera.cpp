#include "Camera.hpp"

void printVec(char* tag,vec4 vec);
void printMat(mat4 mat);
void printrestPoint(char* tag, int x, int y, fixed z);

void Camera::cameraInit(vec3 pos,fixed fov, fixed near, fixed far, int mode)
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
    canvasWidth = fixed(w);
    canvasHeight = fixed(h);
    viewportWidth = fixed(w / 100.f); 
    viewportHeight = fixed(h / 100.f);
    aspect = fxdiv(viewportWidth, viewportHeight); 
    this->fov = fov;
    this->near = near;
    this->far = far;
    this->pos = pos;
    yaw = 0;
    pitch = 0;
    roll = 0;
    lookAt = {0,0,0};
    world2cam = mat4::identity();
    computePerspectiveMat();
}

void Camera::cameraComputeRotMatrix(mat4 &result) 
{
    // TODO: precompute yawPitchRollmatrix
    // ROTMAT =  yaw * pitch * roll
    result = matrix4x4createRotY(yaw) * matrix4x4createRotX(pitch) * matrix4x4createRotZ(roll);
}

void Camera::initWorldToCamspaceMat() //시점변환 행렬
{
    world2cam = mat4::identity();
    vec4 forward = vec4::normalize((pos - lookAt));
    vec4 tmp = {0, fixed(1), 0, 0};
    vec4 right; 
    vec4 up;
    fixed eps = 25; // Is about 0.009; assumes FIX_SHIFT == 8
    // TODO/FIXME: Handling of this special case (camera looking completely down/up) *does not work* at all for non-static scenes (interpolation is messed up).
    if (ABS(forward.x - tmp.x) < eps && ABS(forward.y - tmp.y) < eps && ABS(forward.z - tmp.z) < eps ) { // Special case where the camera looks straight up/down and the cross product "fails".
        right = vecUnit({forward.y, 0,0});
        up = vecUnit(vecCross(forward, right));
    } else {
        right = vecUnit(vecCross(tmp, forward));
        up = vecUnit(vecCross(forward, right));
    }
    matrix4x4SetBasis(world2cam, right, up, forward);
    //printMat(world2cam);
    mat4 rotmat;
    cameraComputeRotMatrix(rotmat);
    world2cam = world2cam * rotmat;
    //printMat(world2cam);
    // Invert the matrix so we get the world-to-camera matrix from our current camera-to-world matrix. 
    // (The transposition of square orthonormal matrices is equivalent to their inversion. If something goes wrong, our matrix is not orthonormal; try the numerical solution.)
    matrix4x4Transpose(world2cam); 

    // Compute translation matrix and put it into 'transMat'.
    mat4 transMat;
    transMat = mat4::identity();
    matrix4x4setIdentity(transMat);
    matrix4x4SetTranslation(transMat, {-pos.x,-pos.y,-pos.z} ); 

    // Post-multiply the translation matrix with the rotation matrix.
    matrix4x4Mul(world2cam, transMat); // world2cam' = world2cam  * transMat 
    //printMat(world2cam);
}

void Camera::computePerspectiveMat()
{
    fixed near = this->near;
    fixed far = this->far;
    fixed top =  fxmul(float2fx(tan(fx2float(this->fov) / 2. )), near);
    fixed bottom = -top;
    fixed right = fxmul(top, this->aspect);
    fixed left = -right;
    //printVec("n,f,t",{near,far,top });
    //printVec("b,r,l",{bottom,right,left});
    fixed persp[16] = {
        fxdiv( fxmul(near, int2fx(2)), right - left), 0, fxdiv(right + left, right - left), 0,
        0, fxdiv(fxmul(near, int2fx(2)), top - bottom), fxdiv(top + bottom, top - bottom), 0,
        0, 0, -fxdiv(far + near, far - near), -fxdiv(fxmul(near, fxmul(int2fx(2), far)), far - near),
        0, 0, int2fx(-1), 0
    }; //4x4 투영변환행렬
    //printMat(persp);
    fixed viewport2image[16] = {
        fxmul(aspect, fxmul(float2fx(0.5), fxdiv(canvasWidth, viewportWidth))), 0, 0,  fxdiv(canvasWidth, int2fx(2)), 
        0, -fxmul(float2fx(0.5), fxdiv(canvasHeight, viewportHeight)), 0, fxdiv(canvasHeight, int2fx(2)), 
        0, 0, int2fx(1), 0,
        0, 0, 0, int2fx(1)
    }; //하드웨어 종횡비 보정
    //printMat(viewport2image);
    memcpy(perspMat, persp, sizeof(persp));
    memcpy(viewport2imageMat, viewport2image, sizeof(viewport2image));

    perspFacX = persp[0];
    perspFacY = persp[5];

    viewportTransFacX = viewport2image[0];
    viewportTransAddX = viewport2image[3];

    viewportTransFacY = viewport2image[5];
    viewportTransAddY = viewport2image[7];

    
    
}

void Camera::applyMatrix(t_obj& obj)
{
    for (int i = 0;i<obj.v_size;i++)
    {
        //printVec("before",obj.vertex[i]);
        //printMat(world2cam);
        //printMat(perspMat);
        //printMat(viewport2imageMat);
        vec4 point = vecTransformed(world2cam,obj.vertex[i]);
        fixed z = -point.z;
        fixed x = fxmul(perspFacX,point.x);
        fixed y = fxmul(perspFacY,point.y);
        //printVec("xyz",{x,y,z});
        printVec("after1",point);
        obj.rest[i].x = fx2int( fxmul(viewportTransFacX, fxdiv(x, z)) + viewportTransAddX );
        obj.rest[i].y = fx2int( fxmul(viewportTransFacY, fxdiv(y, z)) + viewportTransAddY );
        printrestPoint("afterRest", obj.rest[i].x,obj.rest[i].y,obj.vertex[i].z);
    }
}

fixed* Camera::getPerspMat()
{
    return perspMat;
}
fixed* Camera::getw2cMat()
{
    return world2cam;
}

fixed* Camera::getv2iMat()
{
    return viewport2imageMat;
}

void Camera::setLookAt(vec4 dir)
{
    lookAt.x = dir.x;
    lookAt.y = dir.y;
    lookAt.z = dir.z;
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
