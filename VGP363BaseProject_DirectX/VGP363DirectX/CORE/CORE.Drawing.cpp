// CORE.Drawing.cpp
/////////////////////////////////////////////////////

#include "..\GameCore.h"

int CreateColor(int a, int r, int g, int b) {
	int c = (a << 24) + (r << 16) + (g << 8) + (b);
	return c;
}

void ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b) {
	a = pixel >> 24;
	r = (pixel << 8) >> 24;
	g = (pixel << 16) >> 24;
	b = (pixel << 24) >> 24;
}

void PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;

	int index = y * nWidth + x;
	video[index] = color;
}

int BlendColor(int dest, int src, double fGlobalAlpha) {
	unsigned int a1, r1, g1, b1;
	ExtractColor((unsigned int)src, a1, r1, g1, b1);

	unsigned int a2, r2, g2, b2;
	ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	double pixel_alpha = (double)a3 / 255.0;
	fGlobalAlpha *= pixel_alpha;

	r3 = r2 + (unsigned int)(fGlobalAlpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(fGlobalAlpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(fGlobalAlpha * ((int)b1 - (int)b2));

	// Need to use the destination alpha at this point
	return CreateColor(a2, r3, g3, b3);
}

int BlendColor(int dest, int src) {
	unsigned int a1, r1, g1, b1;
	ExtractColor((unsigned int)src, a1, r1, g1, b1);
	double pixel_alpha = a1 / 255.0;

	unsigned int a2, r2, g2, b2;
	ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	
	a3 = a2;
	r3 = r2 + (unsigned int)(pixel_alpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(pixel_alpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(pixel_alpha * ((int)b1 - (int)b2));

	// Need to use the destination alpha at this point
	return CreateColor(255, r3, g3, b3);
}

int GetPixel(int *video, int nWidth, int nHeight, int x, int y)
{
	if(x < 0 || y < 0) return 0;
	if(x >= nWidth || y >= nHeight) return 0;
	int index = y * nWidth + x;
	return video[index];
}

int GetScaledPixel(int *video, int nWidth, int nHeight, double fStretchWidth, double fStretchHeight, int x, int y)
{
	//if(x < 0 || y < 0) return 0;
	//if(x >= (int)fStretchWidth || y >= (int)fStretchHeight) return 0;

	double px = (double)x / fStretchWidth;
	double py = (double)y / fStretchHeight;

	x = (int)(px * (double)nWidth);
	y = (int)(py * (double)nHeight);

	int index = y * nWidth + x;
	return video[index];
}

void PutAlphaPixel(int *video, int nWidth, int nHeight, int x, int y, int color)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;
	if(color == 0) return; // fully transparent
	int index = y * nWidth + x;
	int screen_color = video[index];
	video[index] = BlendColor(screen_color, color);
}

void PutAlphaPixel(int *video, int nWidth, int nHeight, int x, int y, int color, double fGlobalAlpha)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;
	int index = y * nWidth + x;
	int screen_color = video[index];
	video[index] = BlendColor(screen_color, color, fGlobalAlpha);
}

void DrawBox(
	// video memory, and width,height of video memory
	int *video, int nWidth, int nHeight,
	// x, and y location of box, width and height of box, and color
	int x1, int y1, int x2, int y2, int color)
{
	for(int dy=y1; dy<y2; dy++) {
		for(int dx=x1; dx<x2; dx++) {
			PutPixel(video, nWidth, nHeight, dx, dy, color);
		}
	}
}

bool IsTransparent(unsigned int color) {
	int alpha = color >> 24;
	if(alpha == 0) return true;

	// Shift off the alpha
	color = (color << 8) >> 8;

	// Is the color black with zero alpha?
	if(color == CreateColor(0, 255, 255, 255)) {
		return true;
	}
	return false;
}

void DrawBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	for(int y = 0; y < nImageHeight; y++) {
		for(int x = 0; x < nImageWidth; x++) {
			int color = image[y * nImageWidth + x];
			if(!IsTransparent(color)) {
				PutPixel(video, nWidth, nHeight, x + x1, y + y1, color);
			}
		}
	}
}

void DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight) {
	// Draw bitmap, default not flipped
	DrawBitmapCell(video, nWidth, nHeight, xDest, yDest, image, nCellColumn, nCellRow, nCellWidth, nCellHeight, nImageWidth, nImageHeight, false);
}

void DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight, bool bFlipped) {

	int x1 = nCellWidth * nCellColumn;
	int y1 = nCellHeight * nCellRow;
	int x2 = x1 + nCellWidth;
	int y2 = y1 + nCellHeight;

	for(int y = y1; y < y2; y++) {
		for(int x = x1; x < x2; x++) {
			int color; 
			if(bFlipped)
			{ 
				color = image[y * nImageWidth + (x2 - 1 - (x - x1))];
			}
			else
			{ 
				color = image[y * nImageWidth + x];
			}
			if(!IsTransparent(color)) {
				PutPixel(video, nWidth, nHeight, (x - x1) + xDest, (y - y1) + yDest, color);
			}
		}
	}
}

void DrawAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	// Clip to viewport //////////////////////////////////////////////////
	int nImageLeft = 0;
	int nImageTop = 0;
	int nImageRight = nImageWidth;
	int nImageBottom = nImageHeight;
	int x2 = x1 + nImageWidth;
	int y2 = y1 + nImageHeight;
	if(x2 > nWidth) {
		nImageRight = nWidth - x1;
	}
	if(y2 > nHeight) {
		nImageBottom = nHeight - y1;
	}
	if(x1 < 0) {
		nImageLeft = -x1;
		x1 = 0;
	}
	if(y1 < 0) {
		nImageTop = -y1;
		y1 = 0;
	}
	//////////////////////////////////////////////////////////////////////
	for(int y = nImageTop; y < nImageBottom; y++) {
		for(int x = nImageLeft; x < nImageRight; x++) {
			// image position
			int color = GetPixel(image, nImageWidth, nImageHeight, x, y);
			// screen position
			int px = x - nImageLeft, py = y - nImageTop;
			PutAlphaPixel(video, nWidth, nHeight, px + x1, py + y1, color);
		}
	}
}

void DrawStretchedAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight, double fImageStretchWidth, double fImageStretchHeight) {
	// Clip to viewport //////////////////////////////////////////////////
	int nImageLeft = 0;
	int nImageTop = 0;
	double fImageStretchedRight = fImageStretchWidth;
	double fImageStretchedBottom = fImageStretchHeight;
	int x2 = x1 + (int)fImageStretchWidth;
	int y2 = y1 + (int)fImageStretchHeight;
	if(x2 > nWidth) {
		fImageStretchedRight = nWidth - x1;
	}
	if(y2 > nHeight) {
		fImageStretchedBottom = nHeight - y1;
	}
	if(x1 < 0) {
		nImageLeft = -x1;
		x1 = 0;
	}
	if(y1 < 0) {
		nImageTop = -y1;
		y1 = 0;
	}
	//////////////////////////////////////////////////////////////////////
	for(int y = nImageTop; y < (int)fImageStretchedBottom; y++) {
		for(int x = nImageLeft; x < (int)fImageStretchedRight; x++) {
			// image position
			int color = GetScaledPixel(image, nImageWidth, nImageHeight, fImageStretchWidth, fImageStretchHeight, x, y);
			// screen position
			int px = x - nImageLeft, py = y - nImageTop;
			PutAlphaPixel(video, nWidth, nHeight, px + x1, py + y1, color);
		}
	}
}

void DrawAlphaBitmap(double fGlobalAlpha, int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	if(fGlobalAlpha > 1.0) fGlobalAlpha = 1.0;
	if(fGlobalAlpha < 0.0) fGlobalAlpha = 0.0;
	// Clip to viewport //////////////////////////////////////////////////
	int nImageLeft = 0;
	int nImageTop = 0;
	int nImageRight = nImageWidth;
	int nImageBottom = nImageHeight;
	int x2 = x1 + nImageWidth;
	int y2 = y1 + nImageHeight;
	if(x2 > nWidth) {
		nImageRight = nWidth - x1;
	}
	if(y2 > nHeight) {
		nImageBottom = nHeight - y1;
	}
	if(x1 < 0) {
		nImageLeft = -x1;
		x1 = 0;
	}
	if(y1 < 0) {
		nImageTop = -y1;
		y1 = 0;
	}
	//////////////////////////////////////////////////////////////////////
	for(int y = nImageTop; y < nImageBottom; y++) {
		for(int x = nImageLeft; x < nImageRight; x++) {
			// image position
			int color = GetPixel(image, nImageWidth, nImageHeight, x, y);
			// screen position
			int px = x - nImageLeft, py = y - nImageTop;
			PutAlphaPixel(video, nWidth, nHeight, px + x1, py + y1, color, fGlobalAlpha);
		}
	}
}

bool _IsInCircle(int x, int y, int x1, int y1, int x2, int y2) {
	int width = x2 - x1;
	int height = y2 - y1;
	int radius = width / 4;
	int cx = x + (width / 2);
	int cy = y + (height / 2);
	int distance = (int)sqrt((double)(((x-cx)*(x-cx))+(y-cy)*(y-cy)));
	if(distance < radius) return true;
	return false;
}

void DrawCircle(
	// video memory, and width,height of video memory
	int *video, int nWidth, int nHeight,
	// x, and y location of box, width and height of box, and color
	int x1, int y1, int x2, int y2, int color)
{
	for(int dy=y1; dy<y2; dy++) {
		for(int dx=x1; dx<x2; dx++) {
			if(_IsInCircle(dx, dy, x1, y1, x2, y2)) {
				PutPixel(video, nWidth, nHeight, dx, dy, ~0);
			}
		}
	}
}


void ClearVideo(int *video, int nWidth, int nHeight, int color) {
	DrawBox(video, nWidth, nHeight, 0, 0, nWidth-1, nHeight-1, color);
}
