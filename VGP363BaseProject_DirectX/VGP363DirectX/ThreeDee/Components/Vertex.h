// Vertex.h
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include "Constants.h"

namespace ThreeD
{
	class _VERTEX4F
	{
	public:
		_DOUBLE x, y, z, w;
		_VERTEX4F();
		_VERTEX4F(_DOUBLE a, _DOUBLE b, _DOUBLE c, _DOUBLE d);
		void _Set(_DOUBLE a, _DOUBLE b, _DOUBLE c, _DOUBLE d);
		_VERTEX4F operator+(const _VERTEX4F &vt);
		_VERTEX4F operator - (const _VERTEX4F &vt);
		_VERTEX4F operator*(const _VERTEX4F &vt);
		_VERTEX4F operator/(const _VERTEX4F &vt);
		_VERTEX4F operator*(_DOUBLE ft);
		_VERTEX4F operator/(_DOUBLE ft);
		_VERTEX4F& operator=(const _VERTEX4F &vt);
		_DOUBLE _Magnitude();
		void _Normalize();
		static _DOUBLE _DotProduct(const _VERTEX4F &a, const _VERTEX4F &b);
		static _VERTEX4F _CrossProduct(const _VERTEX4F &a, const _VERTEX4F &b);
	};
}