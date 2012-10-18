// CORE.Math.cpp
///////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "..\GameCore.h"

namespace GameCore {
	
	Rect::Rect(int left, int top, int right, int bottom) {
		this->left = left;
		this->top = top;
		this->width = right-left;
		this->height = bottom-top;
		this->right = right;
		this->bottom = bottom;
	}

	bool Math::_IsPointInCircle(int mx, int my, int x, int y, int r) {
		return sqrt((double)((mx-x)*(mx-x)+(my-y)*(my-y))) < (r);
	}

	bool Math::_IsPtInRect(int x, int y, int left, int top, int width, int height) {
		return x >= left && y >= top && x <= (left+width) && y <= (top+height);
	}

	bool Math::_IsPtInRect(int x, int y, Rect &rect) {
		return _IsPtInRect(x, y, rect.left, rect.top, rect.width, rect.height);
	}

	bool Math::_IsRectCollide(Rect &r1, Rect &r2) {
		// Is any point of rect 1 inside rect 2 ?
		if(_IsPtInRect(r1.left,          r1.top,           r2)) return true;
		if(_IsPtInRect(r1.left+r1.width, r1.top,           r2)) return true;
		if(_IsPtInRect(r1.left+r1.width, r1.top+r1.height, r2)) return true;
		if(_IsPtInRect(r1.left,          r1.top+r1.height, r2)) return true;

		// Is any point of rect 2 inside rect 1 ?
		if(_IsPtInRect(r2.left,          r2.top,           r1)) return true;
		if(_IsPtInRect(r2.left+r2.width, r2.top,           r1)) return true;
		if(_IsPtInRect(r2.left+r2.width, r2.top+r2.height, r1)) return true;
		if(_IsPtInRect(r2.left,          r2.top+r2.height, r1)) return true;
	}

}