#pragma once

#include <stdlib.h>
#include <time.h>

#define _DOUBLE float

const _DOUBLE 	PI 			= 3.1415926535897932384;
const _DOUBLE 	TWO_PI 		= 6.2831853071795864769;
const _DOUBLE 	PI_ON_180 	= 0.0174532925199432957;
const _DOUBLE 	INV_PI 		= 0.3183098861837906715;
const _DOUBLE 	INV_TWO_PI 	= 0.1591549430918953358;
const _DOUBLE	HALF_PI		= 1.5707963267948966192313216916398;

const _DOUBLE 	kEpsilon 	= 0.1; 
const _DOUBLE	kHugeValue	= 1.0E10;

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

#define _RandFloat ((float)std::rand() * invRAND_MAX)
#define _RandInt (std::rand())
#define _SeedRand (std::srand(time(NULL)))

#define _PUTPIXEL(p, x, y, width, height, value) ((p)[((y)*(width))+(x)]=(value))

#define _COLOR32_RGBA(r,g,b,a) ((((int)(r))<<24)+(((int)(g))<<16)+(((int)(b))<<8)+((int)(a)))
#define _COLOR32_ARGB(a,r,g,b) ((((int)(a))<<24)+(((int)(r))<<16)+(((int)(g))<<8)+((int)(b)))
#define _COLOR32_ARGB_GET_RED(c) ((((unsigned int)(c))&0x00FF0000)>>16)
#define _COLOR32_ARGB_GET_GREEN(c) ((((unsigned int)(c))&0x0000FF00)>>8)
#define _COLOR32_ARGB_GET_BLUE(c) ((((unsigned int)(c))&0x000000FF))
#define _COLOR32_ARGB_GET_ALPHA(c) ((((unsigned int)(c))&0xFF000000)>>24)

#define _COLOR_BLACK _COLOR32_ARGB(255,0,0,0)

int GetPixel(int *video, int nWidth, int nHeight, int x, int y);

void PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color);

int CreateColor(int a, int r, int g, int b);
