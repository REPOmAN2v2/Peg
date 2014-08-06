#include "include.h"
#include "sdl.h"
#include "draw.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int diameter = 50;
int circles = HEIGHT + ((HEIGHT - 1) / 2) * HEIGHT;
int emptySize = 25;
int removeOne = 1;
int noneSelected = 1;
int held_x = 0, held_y = 0;
const SDL_Color textColor = {255,255,255,255};
const SDL_Color emptyColor = {50,50,50,255};

int main( int argc, char **argv )
{
	if (initialiseSDL() == -1) {
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	gameplay();

	return 0;
}

void gameplay()
{
	Origin origin;
	float dt = 1/60;

	Triangle **triangle = initialiseGame(&origin);
	fprintf(stdout, "DEBUG: Initialised Game\n");
	update(dt, triangle);

	drawGame(triangle, origin);
	events(triangle, origin);
}

Triangle ** initialiseGame(Origin *origin)
{
	// Create a jagged array in the form of a triangle

	Triangle **triangle = (Triangle**)malloc(sizeof(Triangle*) * HEIGHT);

	for (size_t i = 0; i < HEIGHT; i++) {
		triangle[i] = (Triangle*)malloc(sizeof(Triangle) * i+1);
	}

	resize(triangle, origin);

	// Fill it

	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < i+1; j++) {
			triangle[i][j].color = randColor();
			triangle[i][j].act_x = triangle[i][j].mid_x;
			triangle[i][j].act_y = triangle[i][j].mid_y;
			triangle[i][j].status = 1;
			fprintf(stdout, "%d,%d ", triangle[i][j].mid_x, triangle[i][j].mid_y);
		}
		fprintf(stdout, "\n");
	}

	return triangle;
}

void resize(Triangle **triangle, Origin *origin)
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

void update(float dt, Triangle **triangle)
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < i+1; j++) {
			if (triangle[i][j].status != 0) {
				triangle[i][j].act_x = triangle[i][j].act_x - ((triangle[i][j].act_x - triangle[i][j].mid_x) * SPEED * dt);
				triangle[i][j].act_y = triangle[i][j].act_y - ((triangle[i][j].act_y - triangle[i][j].mid_y) * SPEED * dt);
			}
		}
	}
}

void drawGame(Triangle **triangle, Origin origin)
{
	SDL_Rect position = {0,0,0,0};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	drawText(triangle, position);

	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j <= i; j++) {
			if (triangle[i][j].status == 0) {
				SDL_SetRenderDrawColor(renderer, emptyColor.r, emptyColor.g, emptyColor.b, emptyColor.a);
				position.x = triangle[i][j].mid_x - emptySize / 2 + origin.x;
				position.y = triangle[i][j].mid_y - emptySize / 2 + origin.y;
				position.w = emptySize;
				position.h = emptySize;
				SDL_RenderFillRect(renderer, &position);
			} else {
				drawCircle(triangle[i][j].act_x + origin.x, triangle[i][j].act_y + origin.y, diameter / 2, triangle[i][j].color.r, triangle[i][j].color.g, triangle[i][j].color.b, triangle[i][j].color.a);
				fillCircle(triangle[i][j].act_x + origin.x, triangle[i][j].act_y + origin.y, diameter / 2, triangle[i][j].color.r, triangle[i][j].color.g, triangle[i][j].color.b, triangle[i][j].color.a);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

void drawText(Triangle **triangle, SDL_Rect position)
{
	// SDL_Color color = {0,0,0,0};
	char text[100];
	//char *text = (char*)malloc(sizeof(char) * 100);

	if (!noneSelected) {
		// color = triangle[held_y][held_x].color;
		sprintf(text, "Circle %d,%d selected", held_x, held_y);
		//SDLPrint(30, color, position, text);
		fprintf(stdout, "%s\n", text);
	} else {
		// color = textColor;
		strcpy(text, "None Selected");
		//SDLPrint(30, color, position, text);
		fprintf(stdout, "%s\n", text);
	}

	//position.y = 50;

	if (circles == 1) {
		// color = textColor;
		strcpy(text, "You won!");
		//SDLPrint(30, color, position, text);
		fprintf(stdout, "%s\n", text);
	} else {
		sprintf(text, "%d left", circles);
		//SDLPrint(30, color, position, text);
		fprintf(stdout, "%s\n", text);
	}
}

void SDLPrint(int textsize, SDL_Color color, SDL_Rect position, const char *text)
{
	TTF_Font *font = TTF_OpenFont("../resources/FORCED_SQUARE.ttf", textsize);
	SDL_Texture *texture;

	texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(font, text, color));
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);

	SDL_RenderCopy(renderer, texture, NULL, &position);

	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
}

void events(Triangle **triangle, Origin origin)
{
	SDL_Event event;

	while (1) {
		SDL_WaitEvent(&event);

		if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT) {
			for (size_t i = 0; i < HEIGHT; i++) {
				free(triangle[i]);
			}
			free(triangle);
			exit(1);
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			checkCircleClicked(triangle, x,y);
			drawGame(triangle, origin);
			
			fprintf(stdout, "DEBUG: %d,%d\n", x,y);
		}
	}
}

void checkCircleClicked(Triangle **triangle, int x, int y)
{
	pixelToTriangle(triangle, &x, &y);

	if (x != 0 && y !=0) {
		if (removeOne) {
			setEmpty(triangle, x, y);
			circles -= 1;
			removeOne = 0;
		} else if (noneSelected) {
			hold(triangle, x, y);
		} else {
			tryToJumpTo(triangle, x, y);
		}
	} else {
		noneSelected = 1;
	}
}

int pixelToTriangle(Triangle **triangle, int *x, int *y)
{
	for (int i; i < HEIGHT; i++) {
		for (int j; j <= i; j++) {
			if (distance(triangle[i][j].mid_x, triangle[i][j].mid_y, *x, *y) <= diameter / 2) {
				// (x, y) in a circle
				*x = j;
				*y = i;
				fprintf(stdout, "DEBUG: Clicked on circle (%d, %d)\n", *y, *x);
				return 0;
			}
		}
	}

	*x = 0;
	*y = 0;

	fprintf(stdout, "DEBUG: Clicked outside a circle\n");
	return 1;	
}

int distance(int ax, int ay, int bx, int by)
{
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

int setEmpty(Triangle **triangle, int x, int y)
{
	if (triangle[y][x].status != 0) {
		triangle[y][x].status = 0;
		return 1;
	} else {
		return 0;
	}
}

void hold(Triangle **triangle, int x, int y) {
	if (triangle[y][x].status != 0) {
		held_x = x;
		held_y = y;
		noneSelected = 0;
	}
}

void tryToJumpTo(Triangle **triangle, int x, int y) {
	if (triangle[y][x].status == 0) {
		jumpTo(triangle, x, y);
		noneSelected = 1;
	} else {
		hold(triangle, x, y);
	}
}

void jumpTo(Triangle **triangle, int x, int y) {
	if (checkValidAndRemove(triangle, x, y)) {
		triangle[y][x] = triangle[held_y][held_x];
		setEmpty(triangle, held_x, held_y);
		circles -= circles;
	}
}

int checkValidAndRemove(Triangle **triangle, int x, int y) {
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