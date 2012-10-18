// CORE.Quaternion.h
/////////////////////////////////////////////////////////////////////////

#ifndef __CORE_QUATERNION_H_
#define __CORE_QUATERNION_H_

//using namespace System;

namespace GameCore {

	class Point3D;
	class Matrix3D;

	/////////////////////////////////////////////////////////////////////////////////////////////
	//
	// HOW TO PROPERLY USE QUATERNIONS:
	//
	//  (1) You can create a quaternion as follows:
	//          _QUATERNION4F q = _QUATERNION4F::_Create(axis, angle);
	//
	//  (2) You can "concatenate" rotations as follows:
	//          _QUATERNION4F q = _QUATERNION4F::_CreateIdentity();
	//			_QUATERNION4F r1 = _QUATERNION4F::_Create(axis1, angle1);
	//			_QUATERNION4F r2 = _QUATERNION4F::_Create(axis2, angle2);
	//          q = _QUATERNION4F::_Multiply(r1, q); /* IMPORTANT: Order of operations. */
	//          q = _QUATERNION4F::_Multiply(r2, q); /* IMPORTANT: Order of operations. */
	//			/* The rotations are now packed into q */
	//
	//  (3) You can generate a transformation matrix from your quaternion:
	//			// q must be a unit quaternion, if not "_Normalize" first.
	//			// steps (1) and (2) do preserve normal quaternions.
	//			Matrix3D matrix = q._GetUnitMatrix();
	//
	//  (4) Or, you can apply a quaternion directly to a point:
	//          _QUATERNION4F q = _QUATERNION4F::_Create(axis, angle);
	//          Point3D p = { 10.0, 10.0, 10.0, 1.0 };
	//			_QUATERNION4F::_ApplyTransformation(q, p);
	//
	//  (5) You can interpolate between quaternions as follows:
	//			_QUATERNION4F q = _QUATERNION4F::_Interpolate(time, q1, q2);
	//      where, time ranges from 0.0 to 1.0.
	//
	//  About Interpolation: As you know, plain linear interpolation is a straight line between
	//  two points. However think of points on a circle... If you interpolate between them, you
	//  don't remain on the circle and moreover the angle is non-linear! For that purpose we've
	//  implemented Spherical Linear Interpolation, which is linear on the angle.
	//
	/////////////////////////////////////////////////////////////////////////////////////////////

	class _QUATERNION4F {
	public:
		_QUATERNION4F();
		_QUATERNION4F(double qw, double qx, double qy, double qz);
		void _Initialize(double qw, double qx, double qy, double qz);
		void _SetIdentity();

		void _SetEqualTo(const _QUATERNION4F &m);

		double _Length();
		void _Normalize();

		static _QUATERNION4F _Negate(const _QUATERNION4F &q);
		static double _DotProduct(const _QUATERNION4F &q1, const _QUATERNION4F &q2);

		static _QUATERNION4F _Create(Point3D vector, double fAngle);
		static _QUATERNION4F _CreateIdentity();
		static _QUATERNION4F _Add(const _QUATERNION4F &q1, const _QUATERNION4F &q2);
		static _QUATERNION4F _Multiply(const _QUATERNION4F &q1, const _QUATERNION4F &q2);
		static _QUATERNION4F _Multiply(double fScalar, const _QUATERNION4F &q);
		static Point3D _ApplyTransformation(const _QUATERNION4F &q1, const Point3D &p);

		static _QUATERNION4F _Interpolate(double t, const _QUATERNION4F &q1, const _QUATERNION4F &q2);

		Matrix3D _GetUnitMatrix();
		Matrix3D _GetDenormalMatrix();

	public:
		double w, x, y, z;
	};

}

#endif