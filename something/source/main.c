#pragma once

#include <stdio.h>
#include <tonc.h>
#include "./vertex.c"

int main()
{

	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
	m3_fill(CLR_BLACK);

	OBJ obj;
	Vec3 points[4] = {{0,0,0},{1,0,0},{1,1,0},{0,1,0}};
	obj.size = sizeof(points);
	memcpy16(obj.vertex,points,obj.size);

	Vec3 scale = {10,10,10};
	Vec3 rotate = {0,0,0};
	Vec3 trans ={50,50,50};
	vec_world_transform(&obj,scale,rotate,trans);
	m3_plot(points[0].x,points[0].y,CLR_WHITE);
	m3_plot(points[1].x,points[1].y,CLR_WHITE);
	m3_plot(points[2].x,points[2].y,CLR_WHITE);
	m3_plot(points[3].x,points[3].y,CLR_WHITE);

}
