// Matrix.cpp
////////////////////////////////////////////////////////////////////////////////////////////////
#include "Matrix.h"
namespace ThreeD
{
	_MATRIX16F::_MATRIX16F()
	{
		_SetToIdentity();
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F::_MATRIX16F(const _VERTEX4F &right, const _VERTEX4F &up, const _VERTEX4F &forward, const _VERTEX4F &position)
	{
		_MATRIX16F::_Set(right, up, forward, position);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	void _MATRIX16F::_SetToIdentity()
	{
		r0c0 = 1.0; r0c1 = 0.0; r0c2 = 0.0; r0c3 = 0.0;
		r1c0 = 0.0; r1c1 = 1.0; r1c2 = 0.0; r1c3 = 0.0;
		r2c0 = 0.0; r2c1 = 0.0; r2c2 = 1.0; r2c3 = 0.0;
		r3c0 = 0.0; r3c1 = 0.0; r3c2 = 0.0; r3c3 = 1.0;
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	void _MATRIX16F::_Set(const _VERTEX4F &right, const _VERTEX4F &up, const _VERTEX4F &forward, const _VERTEX4F &position)
	{
		r0c0 = right.x; r0c1 = up.x; r0c2 = forward.x; r0c3 = position.x;
		r1c0 = right.y; r1c1 = up.y; r1c2 = forward.y; r1c3 = position.y;
		r2c0 = right.z; r2c1 = up.z; r2c2 = forward.z; r2c3 = position.z;
		r3c0 = right.w; r3c1 = up.w; r3c2 = forward.w; r3c3 = position.w;
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _MATRIX16F::_Multiply(const _VERTEX4F &v)
	{
		return _VERTEX4F(
			r0c0*v.x + r0c1*v.y + r0c2*v.z + r0c3*v.w,
			r1c0*v.x + r1c1*v.y + r1c2*v.z + r1c3*v.w,
			r2c0*v.x + r2c1*v.y + r2c2*v.z + r2c3*v.w,
			r3c0*v.x + r3c1*v.y + r3c2*v.z + r3c3*v.w
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_Scale(_DOUBLE fSX, _DOUBLE fSY, _DOUBLE fSZ)
	{
		return _MATRIX16F(
			_VERTEX4F(fSX, 0.0, 0.0, 0.0),
			_VERTEX4F(0.0, fSY, 0.0, 0.0),
			_VERTEX4F(0.0, 0.0, fSZ, 0.0),
			_VERTEX4F(0.0, 0.0, 0.0, 1.0)
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_Translate(const _VERTEX4F &v)
	{
		return _MATRIX16F(
			_VERTEX4F(1.0, 0.0, 0.0, 0.0),
			_VERTEX4F(0.0, 1.0, 0.0, 0.0),
			_VERTEX4F(0.0, 0.0, 1.0, 0.0),
			_VERTEX4F(v.x, v.y, v.z, 1.0)
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_RotateX(_DOUBLE fDegrees)
	{
		const _DOUBLE PI = 3.141592653;
		_DOUBLE r = fDegrees * PI / 180;
		return _MATRIX16F(
			_VERTEX4F(1.0,	0.0,	0.0,	0.0),
			_VERTEX4F(0.0,	cos(r),	sin(r),	0.0),
			_VERTEX4F(0.0, -sin(r), cos(r), 0.0),
			_VERTEX4F(0.0,	0.0,	0.0,	1.0)
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_RotateY(_DOUBLE fDegrees)
	{
		const _DOUBLE PI = 3.141592653;
		_DOUBLE r = fDegrees * PI / 180;
		return _MATRIX16F(
			_VERTEX4F(cos(r),	0.0,	-sin(r),	0.0),
			_VERTEX4F(	0.0,	1.0,	0.0,		0.0),
			_VERTEX4F(sin(r),	0.0,	cos(r),		0.0),
			_VERTEX4F(	0.0,	0.0,	0.0,		1.0)
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_RotateZ(_DOUBLE fDegrees)
	{
		const _DOUBLE PI = 3.141592653;
		_DOUBLE r = fDegrees * PI / 180;
		return _MATRIX16F(
			_VERTEX4F(	cos(r),	sin(r),	0.0,	0.0),
			_VERTEX4F( -sin(r),	cos(r),	0.0,	0.0),
			_VERTEX4F(	0.0,	0.0,	1.0,	0.0),
			_VERTEX4F(	0.0,	0.0,	0.0,	1.0)
		);
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_Inverse(const _MATRIX16F &matriix)
	{
		return _MATRIX16F();
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_DOUBLE _MATRIX16F::_Determinant(const _MATRIX16F &m)
	{
		return 0.0;
		//return (m.r0c0 * m.r1c1 * m.r2c2 * m.r3c3 + m.r0c1 * m.r1c2 * m.r2c3 * m.r3c0 + 
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	_MATRIX16F _MATRIX16F::_Adjoint(const _MATRIX16F &matriix)
	{
		return _MATRIX16F();
	}
}