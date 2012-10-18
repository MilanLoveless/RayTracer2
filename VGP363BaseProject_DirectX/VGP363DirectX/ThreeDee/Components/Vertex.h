// Vertex.h
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>

namespace ThreeD
{
	class _VERTEX4F
	{
	public:
		double x, y, z, w;
		_VERTEX4F();
		_VERTEX4F(double a, double b, double c, double d);
		void _Set(double a, double b, double c, double d);
		_VERTEX4F operator+(const _VERTEX4F &vt);
		_VERTEX4F operator-(const _VERTEX4F &vt);
		_VERTEX4F operator*(const _VERTEX4F &vt);
		_VERTEX4F operator/(const _VERTEX4F &vt);
		_VERTEX4F operator*(double ft);
		_VERTEX4F operator/(double ft);
		_VERTEX4F& operator=(const _VERTEX4F &vt);
		double _Magnitude();
		void _Normalize();
		double _DotProduct(const _VERTEX4F &a, const _VERTEX4F &b);
		_VERTEX4F _CrossProduct(const _VERTEX4F &a, const _VERTEX4F &b);
	};
}