// CORE.Math.h
///////////////////////////////////////////////////////

#ifndef __CORE_MATH_H_
#define __CORE_MATH_H_

#include <stdio.h>
#include <string.h>

#include "..\GameCore.h"
//using namespace System;

namespace GameCore {

	struct Rect {
		Rect(int left, int top, int right, int bottom);
		int left, top, right, bottom;
		int width, height;
	};

	class Math {
	public:

		static bool _IsPointInCircle(int mx, int my, int x, int y, int r);
		static bool _IsPtInRect(int x, int y, int left, int top, int width, int height);
		static bool _IsPtInRect(int x, int y, Rect &rect);
		static bool _IsRectCollide(Rect &r1, Rect &r2);

	};

}

#endif