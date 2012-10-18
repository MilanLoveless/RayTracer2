// CORE.Drawing.h
///////////////////////////////////////////////////////////

#ifndef __CORE_DRAWING_
#define __CORE_DRAWING_

	int CreateColor(int a, int r, int g, int b);
	int GetPixel(int *video, int nWidth, int nHeight, int x, int y);
	int GetScaledPixel(int *video, int nWidth, int nHeight, double fStretchWidth, double fStretchHeight, int x, int y);
	void PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color);
	void PutAlphaPixel(int *video, int nWidth, int nHeight, int x, int y, int color);
	void DrawBox(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int color);
	void DrawCircle(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int color);
	void DrawBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
	void DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
	void DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight, bool bFlipped);
	void DrawAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
	void DrawStretchedAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight, double fImageStretchWidth, double fImageStretchHeight);
	void DrawAlphaBitmap(double fGlobalAlpha, int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
	void ClearVideo(int *video, int nWidth, int nHeight, int color);

#endif