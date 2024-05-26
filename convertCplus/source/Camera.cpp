#include "Camera.hpp"



void printNrestOBJ(t_obj &obj);
void printrestOBJ(t_obj &obj);
void printMat(mat4 mat);
void printVec(char *tag, vec3 vec);
void printVec(char *tag, vec4 vec);
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
	this->aspect = fixed(w) / h;
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
	result = mat4::rotateY(yaw) * mat4::rotateX(pitch) * mat4::rotateZ(roll);
}

void Camera::initWorldToCamspaceMat() //시점변환 행렬
{
	vec3 const	forward = normalize(lookAt - pos);
	vec3 const	right = normalize(cross((vec3){0, 1, 0}, forward));
	vec3 const	up = cross(forward, right);
	mat4 const	inv_R = {
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		forward.x, forward.y, forward.z, 0,
		0, 0, 0, 1 
	};
	mat4 const	inv_T = mat4::translate(-pos.x, -pos.y, -pos.z);
	this->world2cam = inv_R * inv_T;
}

void Camera::computePerspectiveMat()
{
	fixed const	n = this->near;
	fixed const	f = this->far;
	fixed const	aspect = this->aspect;
	fixed const	a = float(1.0f / float(near));
	// fixed(1.0f / float(near * tan(float(this->fov) / 2.0f)));
	// fixed(1) / (fixed(tan(float(this->fov) / 2.0f )) * near);
	fixed const	b = (n + f) / (f - n);
	fixed const	c = fixed(-2) * f * n / (f - n);

	this->perspMat = (mat4){//초기화 아니라서 있어야해요
		a / aspect, 0, 0, 0,
		0, a, 0, 0,
		0, 0, b, c,
		0, 0, 1, 0
	};
}

void Camera::applyMatrix(t_obj& obj)
{
	for (int i = 0;i<obj.v_size;i++)
	{
		// vec4 point = this->world2cam * obj.vertex[i];
		vec4 point = this->perspMat * this->world2cam * obj.vertex[i];
		point.x /= point.w;
		point.y /= point.w;
        //printVec("one",point);
		// 이제 NDC
		// obj.rest[i].x = (point.x + fixed(1)) * fixed(240) / fixed(2); //fixed::operator+(fixed)
		// obj.rest[i].y = (fixed(1) - point.y) * fixed(160) / fixed(2);
		obj.rest[i].x = int((point.x + 1) * 120); //fixed::operator+(fixed)
		obj.rest[i].y = int((fixed(1) - point.y) * 80);
        //printrestPoint("rest",234,432,0);
		// fixed z = -point.z;
		// fixed x = fxmul(perspFacX,point.x);
		// fixed y = fxmul(perspFacY,point.y);
		// //printVec("xyz",{x,y,z});
		// printVec("after1",point);
		// obj.rest[i].x = fx2int( fxmul(viewportTransFacX, fxdiv(x, z)) + viewportTransAddX );
		// obj.rest[i].y = fx2int( fxmul(viewportTransFacY, fxdiv(y, z)) + viewportTransAddY );
		// printrestPoint("afterRest", obj.rest[i].x,obj.rest[i].y,obj.vertex[i].z);
	}
}

mat4 Camera::getPerspMat()
{
	return perspMat;
}
mat4 Camera::getw2cMat()
{
	return world2cam;
}


void Camera::setLookAt(vec3 dir)
{
	lookAt.x = dir.x;
	lookAt.y = dir.y;
	lookAt.z = dir.z;
}

void Camera::cameraRotateUP(int speed)
{
	pitch+=speed;
}
void Camera::cameraRotateDown(int speed)
{
	pitch-=speed;
}
void Camera::cameraRotateLeft(int speed)
{
	yaw+=speed;
}
void Camera::cameraRotateRight(int speed)
{
	yaw-=speed;
}
