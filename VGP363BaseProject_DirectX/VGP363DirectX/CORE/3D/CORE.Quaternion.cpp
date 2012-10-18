// CORE.Quaternion.cpp
/////////////////////////////////////////////////////////////////////////////////////

#include "..\..\GameCore.h"
#include <math.h>

namespace GameCore {

	///////////////////////////////////////////////////////////////////////
	// Most quaternion formulas were derived from an online source:
	//		www.cprogramming.com/tutorial/3d/quaternions.html
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// The spherical linear interpolation is from the research paper,
	//		[Barrera, Hast, Bengtsson ????]
	// which is also provided in the Research folder.
	///////////////////////////////////////////////////////////////////////

	_QUATERNION4F::_QUATERNION4F()
	{
	}

	_QUATERNION4F::_QUATERNION4F(double qw, double qx, double qy, double qz)
	{
		_Initialize(qw, qx, qy, qz);
	}

	void _QUATERNION4F::_Initialize(double qw, double qx, double qy, double qz)
	{
		_QUATERNION4F &t = *this;
		t.w = qw;
		t.x = qx;
		t.y = qy;
		t.z = qz;
	}

	void _QUATERNION4F::_SetEqualTo(const _QUATERNION4F &q) {
		_QUATERNION4F &t = *this;
		t.w = q.w;
		t.x = q.x;
		t.y = q.y;
		t.z = q.z;
	}

	void _QUATERNION4F::_SetIdentity() {
		_Initialize(1, 0, 0, 0);
	}

	double _QUATERNION4F::_Length() {
		return sqrt(w*w + x*x + y*y + z*z);
	}

	void _QUATERNION4F::_Normalize() {
		double magnitude = _Length();
		w /= magnitude;
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	_QUATERNION4F _QUATERNION4F::_Negate(const _QUATERNION4F &q) {
		// NOTE: This only applies to normalized quaternions
		_QUATERNION4F result;
		result.w = q.w;
		result.x = -q.x;
		result.y = -q.y;
		result.z = -q.z;
		return result;
	}

	double _QUATERNION4F::_DotProduct(const _QUATERNION4F &q1, const _QUATERNION4F &q2) {
		// This is the same dot product as vectors //////////////////////
		return q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
	}

	_QUATERNION4F _QUATERNION4F::_Add(const _QUATERNION4F &q1, const _QUATERNION4F &q2) {
		_QUATERNION4F result;
		result.w = q1.w+q2.w;
		result.x = q1.x+q2.x;
		result.y = q1.y+q2.y;
		result.z = q1.z+q2.z;
		return result;
	}

	_QUATERNION4F _QUATERNION4F::_Multiply(const _QUATERNION4F &q1, const _QUATERNION4F &q2) {
		_QUATERNION4F result;
		result.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
		result.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
		result.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
		result.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
		return result;
	}

	_QUATERNION4F _QUATERNION4F::_Multiply(double fScalar, const _QUATERNION4F &q) {
		_QUATERNION4F result;
		result.w = fScalar * q.w;
		result.x = fScalar * q.x;
		result.y = fScalar * q.y;
		result.z = fScalar * q.z;
		return result;
	}

	_QUATERNION4F _QUATERNION4F::_Create(Point3D vector, double fAngle) {
		_QUATERNION4F result;
		double fHalfAngle = fAngle/2.0;
		result.w = cos(fHalfAngle);
		result.x = vector.x * sin(fHalfAngle);
		result.y = vector.y * sin(fHalfAngle);
		result.z = vector.z * sin(fHalfAngle);
		return result;
	}

	_QUATERNION4F _QUATERNION4F::_CreateIdentity() {
		_QUATERNION4F result;
		result._SetIdentity();
		return result;
	}

	Matrix3D _QUATERNION4F::_GetUnitMatrix() {
		Matrix3D result;
		_QUATERNION4F &t = *this;
		result.r0c0 = 1.0 - 2.0 * t.y*t.y - 2.0 * t.z*t.z;
		result.r0c1 = 2.0 * t.x * t.y - 2.0 * t.w * t.z;
		result.r0c2 = 2.0 * t.x * t.z + 2.0 * t.w * t.y;
		result.r0c3 = 0.0;
		result.r1c0 = 2.0 * t.x * t.y + 2.0 * t.w * t.z;
		result.r1c1 = 1.0 - 2.0 * t.x*t.x - 2.0 * t.z*t.z;
		result.r1c2 = 2.0 * t.y * t.z + 2.0 * t.w * t.x;
		result.r1c3 = 0.0;
		result.r2c0 = 2.0 * t.x * t.z - 2.0 * t.w * t.y;
		result.r2c1 = 2.0 * t.y * t.z - 2.0 * t.w * t.x;
		result.r2c2 = 1.0 - 2.0 * t.x*t.x - 2.0 * t.y*t.y;
		result.r2c3 = 0.0;
		result.r3c0 = 0.0;
		result.r3c1 = 0.0;
		result.r3c2 = 0.0;
		result.r3c3 = 1.0;
		return result;
	}

	Matrix3D _QUATERNION4F::_GetDenormalMatrix() {
		Matrix3D result;
		_QUATERNION4F &t = *this;
		result.r0c0 = t.w*t.w + t.x*t.x - t.y*t.y - t.z*t.z;
		result.r0c1 = 2.0 * t.x * t.y - 2.0 * t.w * t.z;
		result.r0c2 = 2.0 * t.x * t.z + 2.0 * t.w * t.y;
		result.r0c3 = 0.0;
		result.r1c0 = 2.0 * t.x * t.y + 2.0 * t.w * t.z;
		result.r1c1 = t.w*t.w - t.x*t.x + t.y*t.y - t.z*t.z;
		result.r1c2 = 2.0 * t.y * t.z + 2.0 * t.w * t.x;
		result.r1c3 = 0.0;
		result.r2c0 = 2.0 * t.x * t.z - 2.0 * t.w * t.y;
		result.r2c1 = 2.0 * t.y * t.z - 2.0 * t.w * t.x;
		result.r2c2 = t.w*t.w - t.x*t.x - t.y*t.y + t.z*t.z;
		result.r2c3 = 0.0;
		result.r3c0 = 0.0;
		result.r3c1 = 0.0;
		result.r3c2 = 0.0;
		result.r3c3 = 1.0;
		return result;
	}

	Point3D _QUATERNION4F::_ApplyTransformation(const _QUATERNION4F &q, const Point3D &p) {
		Point3D result;
		_QUATERNION4F qP(0, p.x, p.y, p.z);        // The quaternion represention of point
		_QUATERNION4F qInv(q.w, -q.x, -q.y, -q.z); // The inverse quaternion of q
		///////////////////////////////////////////////////////////////////////////////////////
		// result = q * p * q^(-1)
		_QUATERNION4F t = _QUATERNION4F::_Multiply(q, qP);
		t = _QUATERNION4F::_Multiply(t, qInv);
		///////////////////////////////////////////////////////////////////////////////////////
		result.w = t.w;
		result.x = t.x;
		result.y = t.y;
		result.z = t.z;
		/*************************************************************************************/
		// Deviating from research paper slightly and homogonizing the result to make
		// it a valid point with w-component 1.0. If you need to make it a vector you
		// can just set the w-component to 0.0 afterwards.
		result._Homogenize();
		/*************************************************************************************/
		return result;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// _Interpolate : This is pure mathematical spherical linear interpolation of quaternions from [Barrera,
	//  Hast, Bengtsson] which is also recorded in the Research folder. NOTE: Faster forms of this function
	//  are summarized in the paper also. While this is the purest most straight-forward implementation for
	//  correctness, the more optimized versions can be implemented later.
	_QUATERNION4F _QUATERNION4F::_Interpolate(double t, const _QUATERNION4F &q1, const _QUATERNION4F &q2) {
		double theta = acos(_QUATERNION4F::_DotProduct(q1, q2));
		double alpha = sin((1.0 - t)*theta) / sin(theta);
		double beta = sin(t * theta) / sin(theta);
		return _QUATERNION4F::_Add(
			_QUATERNION4F::_Multiply(alpha, q1), 
			_QUATERNION4F::_Multiply(beta, q2)
		);
	}

}