#pragma once

#include <tonc.h>

typedef struct trace
{
    int	error;
	int	x;
	int	dx;
	int	dy;
}trace;

void trace_init(trace * self, POINT p0, POINT p1)
{
    POINT d = {{p1.x-p0.x},{p1.y-p0.y}};
    POINT floor = {{((p0.x + 3) & ~0b111) + 4},{((p0.y + 3) & ~0b111) + 4}};

    self->dx = d.x;
    self->dy = d.y;
    self->error = d.y * (floor.x - p0.x) - d.x * (floor.y - p0.y);
    self->x = floor.x >> 3;

    if (d.y == 0)
		return; // #E
	while (self->error < 0) { //선보다 왼쪽이면
		self->error += d.y * 8; // 1픽셀 이동
		self->x += 1;
	}
	while (self->error - d.y * 8 >= 0) { // 1픽셀 왼쪽으로 가도 선보다 오른쪽이면
		self->error -= d.y * 8; // 1픽셀 왼쪽으로
		self->x -= 1;
	}

}


void trace_move(trace *self) {
	self->error -= self->dx * 8; // 1픽셀만큼 y+
	if (self->dx < 0) {
		while (self->error - self->dy * 8 >= 0) { // 1픽셀 움직인 자리가 선보다 같거나 오른쪽
			self->error -= self->dy * 8;
			self->x -= 1;
		}
	} else {
		while (self->error < 0) { // 현재 자리가 선보다 왼쪽
			self->error += self->dy * 8;
			self->x += 1;
		}
	}
}

void trace_set(trace *ab,trace *ac,trace *bc,Triangle* obj)
{
    trace_init(ab,obj->a,obj->b);
    trace_init(ac,obj->a,obj->c);
    trace_init(bc,obj->b,obj->c);
}