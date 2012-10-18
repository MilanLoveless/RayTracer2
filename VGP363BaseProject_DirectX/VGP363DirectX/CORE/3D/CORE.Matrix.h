// CORE.Matrix.h
/////////////////////////////////////////////////////////////////////////

#ifndef __COREMatrix3D_H_
#define __COREMatrix3D_H_

//using namespace System;

namespace GameCore {

	class Point3D;

	class Matrix3D {
	public:
		Matrix3D();
		Matrix3D(double m[16]);
		void _Initialize(double m[16]);
		void _SetIdentityMatrix();

		Point3D _Multiply(const Point3D &v);
		Matrix3D _Multiply(const Matrix3D &m);

		void _SetEqualTo(const Matrix3D &m);

		void _Scale(double fAmt);
		void _SetPerspective(double fAmt);

		void _TranslateAlongObjectUp(double fAmt);
		void _TranslateAlongObjectForward(double fAmt);
		void _TranslateAlongObjectRight(double fAmt);

		Matrix3D _CreateRotationAroundWorldUpVector(double fAmt);
		Matrix3D _CreateRotationAroundWorldForwardVector(double fAmt);
		Matrix3D _CreateRotationAroundWorldRightVector(double fAmt);

		Matrix3D _CreateTranslateAlongWorldUp(double fAmt);
		Matrix3D _CreateTranslateAlongWorldForward(double fAmt);
		Matrix3D _CreateTranslateAlongWorldRight(double fAmt);

		void _RotateAroundWorldUpVector(double fAmt);
		void _RotateAroundWorldForwardVector(double fAmt);
		void _RotateAroundWorldRightVector(double fAmt);

		void _TranslateAlongWorldUp(double fAmt);
		void _TranslateAlongWorldForward(double fAmt);
		void _TranslateAlongWorldRight(double fAmt);

	public:
		double r0c0, r0c1, r0c2, r0c3;
		double r1c0, r1c1, r1c2, r1c3;
		double r2c0, r2c1, r2c2, r2c3;
		double r3c0, r3c1, r3c2, r3c3;
	};

}

#endif