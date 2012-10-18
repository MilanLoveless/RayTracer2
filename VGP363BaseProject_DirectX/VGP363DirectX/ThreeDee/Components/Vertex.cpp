// Vertex.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vertex.h"

namespace ThreeD
{
	void _VERTEX4F::_Set(double a, double b, double c, double d)
	{
		this->x=a;
		this->y=b;
		this->z=c;
		this->w=d;
	}
	_VERTEX4F::_VERTEX4F()
	{
		this->_Set(0.0, 0.0, 0.0, 1.0);
	}
	_VERTEX4F::_VERTEX4F(double a, double b, double c, double d)
	{
		this->_Set(a, b, c, d);
	}
	double _VERTEX4F::_Magnitude()
	{
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
	}
	void _VERTEX4F::_Normalize()
	{
		double m = _Magnitude();
		this->x /= m; this->y /= m;
		this->z /= m; this->w /= m;
	}


	_VERTEX4F _VERTEX4F::operator + (const _VERTEX4F &vt)
	{
		return _VERTEX4F(this->x + vt.x, this->y + vt.y, this->z + vt.z, this->w + vt.w);
	}
	_VERTEX4F _VERTEX4F::operator - (const _VERTEX4F &vt)
	{
		return _VERTEX4F(this->x - vt.x, this->y - vt.y, this->z - vt.z, this->w - vt.w);
	}
	_VERTEX4F _VERTEX4F::operator * (const _VERTEX4F &vt)
	{
		return _VERTEX4F(this->x * vt.x, this->y * vt.y, this->z * vt.z, this->w * vt.w);
	}
	_VERTEX4F _VERTEX4F::operator / (const _VERTEX4F &vt)
	{
		return _VERTEX4F(this->x / vt.x, this->y / vt.y, this->z / vt.z, this->w / vt.w);
	}
	_VERTEX4F _VERTEX4F::operator * (double Scalar)
	{
		return _VERTEX4F(this->x * Scalar, this->y * Scalar, this->z * Scalar, this->w * Scalar);
	}
	_VERTEX4F _VERTEX4F::operator / (double Scalar)
	{
		return _VERTEX4F(this->x / Scalar, this->y / Scalar, this->z / Scalar, this->w / Scalar);
	}

	double _VERTEX4F::_DotProduct(const _VERTEX4F &a, const _VERTEX4F &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	_VERTEX4F _VERTEX4F::_CrossProduct(const _VERTEX4F &a, const _VERTEX4F &b)
	{
		return _VERTEX4F(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0.0);
	}

	_VERTEX4F& _VERTEX4F::operator=(const _VERTEX4F &vt)
	{
		x = vt.x;
		y = vt.y;
		z = vt.z;
		w = vt.w;

		return (*this);
	}
}