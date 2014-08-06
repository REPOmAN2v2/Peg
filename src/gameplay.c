#include <math.h>

#include "gameplay.h"
#include "draw.h"

void checkCircleClicked(Triangle triangle[][HEIGHT], Origin origin, int x, int y)
{
	pixelToTriangle(triangle, &x, &y);

	if (x != -1 && y != -1) {
		if (removeOne) {
			fprintf(stdout, "DEBUG: First circle to remove: (%d, %d)\n", x, y);
			setEmpty(triangle, x, y);
			circles -= 1;
			removeOne = 0;
			drawGame(triangle, origin);
		} else if (noneSelected) {
			fprintf(stdout, "DEBUG: Moving (%d, %d)\n", x, y);
			hold(triangle, x, y);
		} else {
			fprintf(stdout, "DEBUG: Check if moveable to (%d, %d)\n", x, y);
			tryToJumpTo(triangle, origin, x, y);
		}
	} else {
		noneSelected = 1;
	}
}

int pixelToTriangle(Triangle triangle[][HEIGHT], int *x, int *y)
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j <= i; j++) {
			if (distance(triangle[i][j].mid_x, triangle[i][j].mid_y, *x, *y) <= (diameter / 2)) {
				// (x, y) in a circle
				*x = j;
				*y = i;
				fprintf(stdout, "DEBUG: Clicked on circle (%d, %d)\n", *x, *y);
				return 0;
			}
		}
	}

	*x = -1;
	*y = -1;

	fprintf(stdout, "DEBUG: Clicked outside a circle\n");
	return 1;	
}

int distance(int ax, int ay, int bx, int by)
{
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

int setEmpty(Triangle triangle[][HEIGHT], int x, int y)
{
	if (triangle[y][x].status != 0) {
		triangle[y][x].status = 0;
		fprintf(stdout, "DEBUG: triangle (%d, %d) set empty\n", x, y);
		return 1;
	} else {
		return 0;
	}
}

void hold(Triangle triangle[][HEIGHT], int x, int y) {
	if (triangle[y][x].status != 0) {
		held_x = x;
		held_y = y;
		noneSelected = 0;
		fprintf(stdout, "DEBUG: Now holding (%d, %d)\n", x, y);
	}
}

void tryToJumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y) {
	if (triangle[y][x].status == 0) {
		jumpTo(triangle, origin, x, y);
		noneSelected = 1;
	} else {
		hold(triangle, x, y);
	}
}

void jumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y) {
	if (checkValidAndRemove(triangle, x, y)) {
		triangle[y][x].color = triangle[held_y][held_x].color;
		triangle[y][x].status = 1;
		setEmpty(triangle, held_x, held_y);
		circles -= 1;
		drawGame(triangle, origin);
	}
}

int checkValidAndRemove(Triangle triangle[][HEIGHT], int x, int y) {
	if (held_x == x) {
		if (held_y - 2 == y) {
			return setEmpty(triangle, held_x, held_y - 1);
		} else if (held_y + 2 == y) {
			return setEmpty(triangle, held_x, held_y + 1);
		}
	} else if (held_x - 2 == x) {
		if (held_y - 2 == y) {
			return setEmpty(triangle, held_x - 1, held_y - 1);
		} else if (held_y == y) {
			return setEmpty(triangle, held_x - 1, held_y);
		}
	} else if (held_x + 2 == x) {
		if (held_y == y) {
			return setEmpty(triangle, held_x + 1, held_y);
		} else if (held_y + 2 == y) {
			return setEmpty(triangle, held_x + 1, held_y + 1);
		}
	}

	return 0;
}