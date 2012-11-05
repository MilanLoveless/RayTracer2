// Point2D.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Point2D.h"

namespace ThreeD
{

	_POINT2D::_POINT2D()
	{
		x = 0.0;
		y = 0.0;
	}

	_POINT2D::_POINT2D(const _DOUBLE arg)
	{
		x = arg;
		y = arg;
	}

	_POINT2D::_POINT2D(const _POINT2D &p)
	{
		x = p.x;
		y = p.y;
	}

	_POINT2D::~_POINT2D()
	{

	}

	_POINT2D& _POINT2D::operator= (const _POINT2D &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return (*this);
	}

	_POINT2D _POINT2D::operator* (const _DOUBLE a)
	{
		return (_POINT2D(x * a, y * a));
	}

}