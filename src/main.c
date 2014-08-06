#include <time.h>

#include "include.h"
#include "sdl.h"
#include "draw.h"
#include "gameplay.h"
#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int diameter, circles, removeOne, noneSelected, held_x, held_y;

const int emptySize = 25;
const SDL_Color textColor = {255,255,255,255};
const SDL_Color emptyColor = {50,50,50,255};

int main( int argc, char **argv )
{
	if (initialiseSDL() == -1) {
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	Origin origin;
	Triangle triangle[HEIGHT][HEIGHT];

	gameplay(triangle, origin);

	return 0;
}