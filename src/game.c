#include <math.h>

#include "game.h"
#include "gameplay.h"
#include "draw.h"

void gameplay(Triangle triangle[][HEIGHT], Origin origin)
{
	do {
		diameter = 50;
		circles = HEIGHT + ((HEIGHT - 1) / 2) * HEIGHT;
		removeOne = 1;
		noneSelected = 1;
		held_x = -1;
		held_y = -1;

		initialiseGame(triangle, &origin);
		fprintf(stdout, "DEBUG: Initialised Game\n");

		drawGame(triangle, origin);
	} while (events(triangle, origin));
}

void initialiseGame(Triangle triangle[][HEIGHT], Origin *origin)
{
	// Create a jagged array in the form of a triangle

	/*Triangle **triangle = (Triangle**)malloc(sizeof(Triangle*) * HEIGHT);

	for (size_t i = 0; i < HEIGHT; i++) {
		triangle[i] = (Triangle*)malloc(sizeof(Triangle) * i+1);
	}*/

	resize(triangle, origin);

	// Fill it

	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < i+1; j++) {
			triangle[i][j].color = randColor();
			triangle[i][j].status = 1;
			fprintf(stdout, "%d,%d ", triangle[i][j].mid_x, triangle[i][j].mid_y);
		}
		fprintf(stdout, "\n");
	}
}

void resize(Triangle triangle[][HEIGHT], Origin *origin)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	diameter = w / (HEIGHT * 2);
	if (diameter * (HEIGHT * 2) > h) {
		diameter = h / (HEIGHT * 2);
	}

	fprintf(stdout, "DEBUG: diameter: %d\n", diameter);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j <= i; j++) {
			triangle[i][j].mid_x = diameter * (2 * j + (HEIGHT - i - 0.5));
			triangle[i][j].mid_y = diameter * (i+1) * ((1 + sqrt(5)) / 2) - (diameter);
		}
	}

	origin->x = (w - diameter * (HEIGHT * 2 - 1)) / 2;
	origin->y = (h - diameter * (HEIGHT * 2 - 1)) / 2;
}

SDL_Color randColor()
{
	SDL_Color color;
	color.r = rand()%255 + 1;
	color.g = rand()%255 + 1;
	color.b = rand()%255 + 1;
	color.a = 255;

	return color;
}



int events(Triangle triangle[][HEIGHT], Origin origin)
{
	SDL_Event event;
	int x, y;

	while (1) {
		SDL_WaitEvent(&event);

		if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT) {
			/*for (size_t i = 0; i < HEIGHT; i++) {
				free(triangle[i]);
			}
			free(triangle);*/
			return 0;
		} else if (event.key.keysym.sym == SDLK_r) {
			return 1;
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&x, &y);
			checkCircleClicked(triangle, origin, x - origin.x, y - origin.y);
			// drawGame(triangle, origin);
			
			fprintf(stdout, "DEBUG: %d,%d\n", x,y);
		}
	}
}