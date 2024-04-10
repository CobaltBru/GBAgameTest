#include <stdio.h>
#include <tonc.h>

#include "../include/Circle.h"

int main()
{

	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	VECTOR center;
	FIXED radius = 50;
	COLOR color = CLR_RED;

	vec_set(&center, int2fx(M3_WIDTH / 2), int2fx(M3_HEIGHT / 2), int2fx(0));
	Circle circle = {center, radius, color};

	for (int j = 0; j < M3_HEIGHT; j++)
	{
		for (int i = 0; i < M3_WIDTH; i++)
		{
			VECTOR tmp;
			vec_set(&tmp, i, j, 0);
			if (!IsInside(&circle, &tmp))
			{
				vid_mem[j * M3_WIDTH + i] = circle.color;
			}
		}
	}

	while (1);
	return 0;
}
