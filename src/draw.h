#ifndef DRAW_H__
#define DRAW_H__

#include "include.h"

int drawCircle(Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int fillCircle(Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int drawLine(Sint16 x1, Sint16 x2, Sint16 y);
int pixelRGBA(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int pixelRGBAWeight(Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight);

#endif