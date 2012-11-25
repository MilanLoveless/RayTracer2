// Matrix.h
/////////////////////////////////////////////////////////////////////

#pragma once
#include "Vertex.h"
#include "Constants.h"

namespace ThreeD
{
	class _MATRIX16F
	{
	public:
		_MATRIX16F();
		_MATRIX16F(const _VERTEX4F &right, const _VERTEX4F &up, const _VERTEX4F &forward, const _VERTEX4F &position);
		void _SetToIdentity();
		void _Set(const _VERTEX4F &right, const _VERTEX4F &up, const _VERTEX4F &forward, const _VERTEX4F &position);
		
		_VERTEX4F _Multiply(const _VERTEX4F &v);

		static _MATRIX16F _Scale(_DOUBLE fSX, _DOUBLE fSY, _DOUBLE fSZ);
		static _MATRIX16F _Translate(const _VERTEX4F &vector);
		static _MATRIX16F _RotateX(_DOUBLE fDegrees);
		static _MATRIX16F _RotateY(_DOUBLE fDegrees);
		static _MATRIX16F _RotateZ(_DOUBLE fDegrees);
		static _MATRIX16F _Inverse(const _MATRIX16F &m);
		static _DOUBLE _Determinant(const _MATRIX16F &m);
		static _MATRIX16F _Adjoint(const _MATRIX16F &m);

		_DOUBLE r0c0, r0c1, r0c2, r0c3;
		_DOUBLE r1c0, r1c1, r1c2, r1c3;
		_DOUBLE r2c0, r2c1, r2c2, r2c3;
		_DOUBLE r3c0, r3c1, r3c2, r3c3;
	};
}