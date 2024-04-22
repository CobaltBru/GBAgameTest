#pragma once

#include <stdio.h>
#include <tonc.h>

#include "../include/model.h"
#include "../include/scanline.h"
#include "../include/span.h"
#include "../include/trace.h"

void scanline_test(Triangle obj)
{
	trace ab;
	trace ac;
	trace bc;
	span top;
	span bottom;
	scanline sline;

	trace_set(&ab,&ac,&bc,&obj);

	int	high = (((obj.a.y + 3) & ~0b111) + 4) >> 3;
	int	mid = (((obj.b.y + 3) & ~0b111) + 4) >> 3;
	int	low = (((obj.c.y + 3) & ~0b111) + 4) >> 3;

	if (obj.b.x < obj.c.x) {
		span_init(&top, &ab, &ac, high, mid);
		span_init(&bottom, &bc, &ac, mid, low);
	} else {
		span_init(&top, &ac, &ab, high, mid);
		span_init(&bottom, &ac, &bc, mid, low);
	}
	scanline_init(&sline);
	scanline_push(&sline, &top);
	scanline_push(&sline, &bottom);
	scanline_sort(&sline);
	for (int y = 0; y < M3_HEIGHT; ++y) {
		scanline_move(&sline);
		for (int x = 0; x < M3_WIDTH; ++x) {
			if (sline.active != &sline.active_end && sline.active->left->x <= x && x < sline.active->right->x)
				m3_plot(x,y,CLR_WHITE);
		}
	}
}

int main()
{

	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
	m3_fill(CLR_BLACK);

	Triangle tri;
	POINT a = {50, 10};
	POINT b = {100, 50};
	POINT c = {50, 130};
	initTriangle(&tri, a, b, c);

	scanline_test(tri);

	while (1)
		;
	return 0;
}
