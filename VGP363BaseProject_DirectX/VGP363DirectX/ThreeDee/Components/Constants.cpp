// constants.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Constants.h"

int CreateColor(int a, int r, int g, int b) {
	int c = (a << 24) + (r << 16) + (g << 8) + (b);
	return c;
}

int GetPixel(int *video, int nWidth, int nHeight, int x, int y)
{
	if(x < 0 || y < 0) return 0;
	if(x >= nWidth || y >= nHeight) return 0;
	int index = y * nWidth + x;
	return video[index];
}


void PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;

	int index = y * nWidth + x;
	video[index] = color;
}