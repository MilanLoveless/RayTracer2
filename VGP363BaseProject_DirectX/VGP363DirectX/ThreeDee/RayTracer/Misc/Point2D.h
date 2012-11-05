// Point2D.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Constants.h"

namespace ThreeD
{

	class _POINT2D
	{
	public:
		_DOUBLE x, y;

		_POINT2D();
		_POINT2D(const _DOUBLE arg);
		_POINT2D(const _DOUBLE x1, const _DOUBLE y1);
		_POINT2D(const _POINT2D &p);
		~_POINT2D();

		_POINT2D& operator= (const _POINT2D &rhs);
		_POINT2D operator * (const _DOUBLE a);
	};

}