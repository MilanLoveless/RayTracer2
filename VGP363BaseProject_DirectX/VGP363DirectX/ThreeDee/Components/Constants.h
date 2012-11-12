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

const _DOUBLE 	kEpsilon 	= 0.0001; 
const _DOUBLE	kHugeValue	= 1.0E10;

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

#define _RandFloat ((float)std::rand() * invRAND_MAX)
#define _RandInt (std::rand())
#define _SeedRand (std::srand(time(NULL)))


