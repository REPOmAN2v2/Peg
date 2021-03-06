#include <math.h>

#include "draw.h"

void drawGame(Triangle triangle[][HEIGHT], Origin origin)
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
				drawCircle(triangle[i][j].mid_x + origin.x, triangle[i][j].mid_y + origin.y, diameter / 2, triangle[i][j].color.r, triangle[i][j].color.g, triangle[i][j].color.b, triangle[i][j].color.a);
				fillCircle(triangle[i][j].mid_x + origin.x, triangle[i][j].mid_y + origin.y, diameter / 2, triangle[i][j].color.r, triangle[i][j].color.g, triangle[i][j].color.b, triangle[i][j].color.a);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

void drawText(Triangle triangle[][HEIGHT], SDL_Rect position)
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

/* Adapted from SDL2_gfx */

int fillCircle(Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmj, xpj;
	int xmk, xpk;

	if (rad < 0) {
		return (-1);
	}

	/*
	* Set color
	*/
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	/*
	* Init vars 
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw 
	*/
	ix = 0;
	iy = rad * 64;

	do {
		h = (ix + 32) >> 6;
		i = (iy + 32) >> 6;
		j = h;
		k = i;

		if ((oi != i) && (oh != i)) {
			xmj = x - j;
			xpj = x + j;
			if (i > 0) {
				result |= drawLine(xmj, xpj, y + i);
				result |= drawLine(xmj, xpj, y - i);
			} else {
				result |= drawLine(xmj, xpj, y);
			}
			oi = i;
		}
		if ((oh != h) && (oi != h) && (i != h)) {
			xmk = x - k;
			xpk = x + k;
			if (h > 0) {
				result |= drawLine(xmk, xpk, y + h);
				result |= drawLine(xmk, xpk, y - h);
			} else {
				result |= drawLine(xmk, xpk, y);
			}
			oh = h;
		}

		ix = ix + iy / rad;
		iy = iy - ix / rad;

	} while (i > h);


	return (result);
}

int drawCircle(Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result;
	int i;
	int a2, b2, ds, dt, dxt, t, s, d;
	Sint16 xp, yp, xs, ys, dyt, od, xx, yy, xc2, yc2;
	float cp;
	double sab;
	Uint8 weight, iweight;

	if (rad < 0) {
		return (-1);
	}

	/* Variable setup */
	a2 = rad*rad;
	b2 = rad*rad;

	ds = 2 * a2;
	dt = 2 * b2;

	xc2 = 2 * x;
	yc2 = 2 * y;

	sab = sqrt((double)(a2 + b2));
	od = (Sint16)lrint(sab*0.01) + 1; /* introduce some overdraw */
	dxt = (Sint16)lrint((double)a2 / sab) + od;

	t = 0;
	s = -2 * a2 * rad;
	d = 0;

	xp = x;
	yp = y - rad;

	/* Draw */
	result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);

	/* "End points" */
	result |= pixelRGBA(xp, yp, r, g, b, a);
	result |= pixelRGBA(xc2 - xp, yp, r, g, b, a);
	result |= pixelRGBA(xp, yc2 - yp, r, g, b, a);
	result |= pixelRGBA(xc2 - xp, yc2 - yp, r, g, b, a);

	for (i = 1; i <= dxt; i++) {
		xp--;
		d += t - b2;

		if (d >= 0)
			ys = yp - 1;
		else if ((d - s - a2) > 0) {
			if ((2 * d - s - a2) >= 0)
				ys = yp + 1;
			else {
				ys = yp;
				yp++;
				d -= s + a2;
				s += ds;
			}
		} else {
			yp++;
			ys = yp + 1;
			d -= s + a2;
			s += ds;
		}

		t -= dt;

		/* Calculate alpha */
		if (s != 0) {
			cp = (float) abs(d) / (float) abs(s);
			if (cp > 1.0) {
				cp = 1.0;
			}
		} else {
			cp = 1.0;
		}

		/* Calculate weights */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Upper half */
		xx = xc2 - xp;
		result |= pixelRGBAWeight(xp, yp, r, g, b, a, iweight);
		result |= pixelRGBAWeight(xx, yp, r, g, b, a, iweight);

		result |= pixelRGBAWeight(xp, ys, r, g, b, a, weight);
		result |= pixelRGBAWeight(xx, ys, r, g, b, a, weight);

		/* Lower half */
		yy = yc2 - yp;
		result |= pixelRGBAWeight(xp, yy, r, g, b, a, iweight);
		result |= pixelRGBAWeight(xx, yy, r, g, b, a, iweight);

		yy = yc2 - ys;
		result |= pixelRGBAWeight(xp, yy, r, g, b, a, weight);
		result |= pixelRGBAWeight(xx, yy, r, g, b, a, weight);
	}

	/* Replaces original approximation code dyt = abs(yp - yc); */
	dyt = (Sint16)lrint((double)b2 / sab ) + od;    

	for (i = 1; i <= dyt; i++) {
		yp++;
		d -= s + a2;

		if (d <= 0)
			xs = xp + 1;
		else if ((d + t - b2) < 0) {
			if ((2 * d + t - b2) <= 0)
				xs = xp - 1;
			else {
				xs = xp;
				xp--;
				d += t - b2;
				t -= dt;
			}
		} else {
			xp--;
			xs = xp - 1;
			d += t - b2;
			t -= dt;
		}

		s += ds;

		/* Calculate alpha */
		if (t != 0) {
			cp = (float) abs(d) / (float) abs(t);
			if (cp > 1.0) {
				cp = 1.0;
			}
		} else {
			cp = 1.0;
		}

		/* Calculate weight */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Left half */
		xx = xc2 - xp;
		yy = yc2 - yp;
		result |= pixelRGBAWeight(xp, yp, r, g, b, a, iweight);
		result |= pixelRGBAWeight(xx, yp, r, g, b, a, iweight);

		result |= pixelRGBAWeight(xp, yy, r, g, b, a, iweight);
		result |= pixelRGBAWeight(xx, yy, r, g, b, a, iweight);

		/* Right half */
		xx = xc2 - xs;
		result |= pixelRGBAWeight(xs, yp, r, g, b, a, weight);
		result |= pixelRGBAWeight(xx, yp, r, g, b, a, weight);

		result |= pixelRGBAWeight(xs, yy, r, g, b, a, weight);
		result |= pixelRGBAWeight(xx, yy, r, g, b, a, weight);		
	}

	return (result);
}

int pixelRGBA(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawPoint(renderer, x, y);
	return result;
}

int pixelRGBAWeight(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight)
{
	/*
	* Modify Alpha by weight 
	*/
	Uint32 ax = a;
	ax = ((ax * weight) >> 8);
	if (ax > 255) {
		a = 255;
	} else {
		a = (Uint8)(ax & 0x000000ff);
	}

	return pixelRGBA(x, y, r, g, b, a);
}

int drawLine(Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);
}