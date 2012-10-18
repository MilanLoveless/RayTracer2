// CORE.Matrix.cpp
/////////////////////////////////////////////////////////////////////////////////////

#include "..\..\GameCore.h"
#include <math.h>

namespace GameCore {

	Matrix3D::Matrix3D()
	{
	}

	Matrix3D::Matrix3D(double m[16])
	{
		_Initialize(m);
	}

	void Matrix3D::_Initialize(double m[16])
	{
		r0c0=m[0]; r0c1=m[1]; r0c2=m[2]; r0c3=m[3]; 
		r1c0=m[4]; r1c1=m[5]; r1c2=m[6]; r1c3=m[7]; 
		r2c0=m[8]; r2c1=m[9]; r2c2=m[10]; r2c3=m[11]; 
		r3c0=m[12]; r3c1=m[13]; r3c2=m[14]; r3c3=m[15]; 
	}

	Point3D Matrix3D::_Multiply(const Point3D &v) {
		Point3D result = v;
		result.x = r0c0*v.x + r0c1*v.y + r0c2*v.z + r0c3*v.w;
		result.y = r1c0*v.x + r1c1*v.y + r1c2*v.z + r1c3*v.w;
		result.z = r2c0*v.x + r2c1*v.y + r2c2*v.z + r2c3*v.w;
		result.w = r3c0*v.x + r3c1*v.y + r3c2*v.z + r3c3*v.w;
		return result;
	}

	Matrix3D Matrix3D::_Multiply(const Matrix3D &m) {
		Matrix3D result;
		Matrix3D &t = *this;
		result.r0c0 = t.r0c0*m.r0c0 + t.r0c1*m.r1c0 + t.r0c2*m.r2c0 + t.r0c3*m.r3c0;
		result.r0c1 = t.r0c0*m.r0c1 + t.r0c1*m.r1c1 + t.r0c2*m.r2c1 + t.r0c3*m.r3c1;
		result.r0c2 = t.r0c0*m.r0c2 + t.r0c1*m.r1c2 + t.r0c2*m.r2c2 + t.r0c3*m.r3c2;
		result.r0c3 = t.r0c0*m.r0c3 + t.r0c1*m.r1c3 + t.r0c2*m.r2c3 + t.r0c3*m.r3c3;
		result.r1c0 = t.r1c0*m.r0c0 + t.r1c1*m.r1c0 + t.r1c2*m.r2c0 + t.r1c3*m.r3c0;
		result.r1c1 = t.r1c0*m.r0c1 + t.r1c1*m.r1c1 + t.r1c2*m.r2c1 + t.r1c3*m.r3c1;
		result.r1c2 = t.r1c0*m.r0c2 + t.r1c1*m.r1c2 + t.r1c2*m.r2c2 + t.r1c3*m.r3c2;
		result.r1c3 = t.r1c0*m.r0c3 + t.r1c1*m.r1c3 + t.r1c2*m.r2c3 + t.r1c3*m.r3c3;
		result.r2c0 = t.r2c0*m.r0c0 + t.r2c1*m.r1c0 + t.r2c2*m.r2c0 + t.r2c3*m.r3c0;
		result.r2c1 = t.r2c0*m.r0c1 + t.r2c1*m.r1c1 + t.r2c2*m.r2c1 + t.r2c3*m.r3c1;
		result.r2c2 = t.r2c0*m.r0c2 + t.r2c1*m.r1c2 + t.r2c2*m.r2c2 + t.r2c3*m.r3c2;
		result.r2c3 = t.r2c0*m.r0c3 + t.r2c1*m.r1c3 + t.r2c2*m.r2c3 + t.r2c3*m.r3c3;
		result.r3c0 = t.r3c0*m.r0c0 + t.r3c1*m.r1c0 + t.r3c2*m.r2c0 + t.r3c3*m.r3c0;
		result.r3c1 = t.r3c0*m.r0c1 + t.r3c1*m.r1c1 + t.r3c2*m.r2c1 + t.r3c3*m.r3c1;
		result.r3c2 = t.r3c0*m.r0c2 + t.r3c1*m.r1c2 + t.r3c2*m.r2c2 + t.r3c3*m.r3c2;
		result.r3c3 = t.r3c0*m.r0c3 + t.r3c1*m.r1c3 + t.r3c2*m.r2c3 + t.r3c3*m.r3c3;
		return result;
	}

	void Matrix3D::_SetEqualTo(const Matrix3D &m) {
		Matrix3D &t = *this;
		t.r0c0 = m.r0c0;
		t.r0c1 = m.r0c1;
		t.r0c2 = m.r0c2;
		t.r0c3 = m.r0c3;
		t.r1c0 = m.r1c0;
		t.r1c1 = m.r1c1;
		t.r1c2 = m.r1c2;
		t.r1c3 = m.r1c3;
		t.r2c0 = m.r2c0;
		t.r2c1 = m.r2c1;
		t.r2c2 = m.r2c2;
		t.r2c3 = m.r2c3;
		t.r3c0 = m.r3c0;
		t.r3c1 = m.r3c1;
		t.r3c2 = m.r3c2;
		t.r3c3 = m.r3c3;
	}

	void Matrix3D::_Scale(double fAmt) {
		// The scale matrix consists of scale amounts
		// applied to the diagonals of the matrix.
		r0c0 *= fAmt;
		r1c1 *= fAmt;
		r2c2 *= fAmt;
		// (but not to the W-component)
	}

	void Matrix3D::_SetPerspective(double fAmt) {
		// This sets the necessary value in order to scale
		// the W component by the perspective. The user
		// needs to ensure all resultant vectors are
		// homogonized after using a matrix like this.
		r3c2 = fAmt;
		r3c3 = 0.0;

		if(r3c2 == 0.0) {
			r3c3 = 1.0;
		}
	}

	void Matrix3D::_SetIdentityMatrix() {
		double m[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		_Initialize(m);
	}

	#define _RIGHT_X r0c0
	#define _RIGHT_Y r1c0
	#define _RIGHT_Z r2c0
	#define _RIGHT_W r3c0

	#define _FORWARD_X r0c2
	#define _FORWARD_Y r1c2
	#define _FORWARD_Z r2c2
	#define _FORWARD_W r3c2

	#define _UP_X r0c1
	#define _UP_Y r1c1
	#define _UP_Z r2c1
	#define _UP_W r3c1

	#define _POSITION_X r0c3
	#define _POSITION_Y r1c3
	#define _POSITION_Z r2c3
	#define _POSITION_W r3c3

	void Matrix3D::_TranslateAlongObjectUp(double fAmt) {
		_POSITION_X += fAmt * _UP_X;
		_POSITION_Y += fAmt * _UP_Y;
		_POSITION_Z += fAmt * _UP_Z;
		_POSITION_W += fAmt * _UP_W;
	}

	void Matrix3D::_TranslateAlongObjectForward(double fAmt) {
		_POSITION_X += fAmt * _FORWARD_X;
		_POSITION_Y += fAmt * _FORWARD_Y;
		_POSITION_Z += fAmt * _FORWARD_Z;
		_POSITION_W += fAmt * _FORWARD_W;
	}

	void Matrix3D::_TranslateAlongObjectRight(double fAmt) {
		_POSITION_X += fAmt * _RIGHT_X;
		_POSITION_Y += fAmt * _RIGHT_Y;
		_POSITION_Z += fAmt * _RIGHT_Z;
		_POSITION_W += fAmt * _RIGHT_W;
	}

	Matrix3D Matrix3D::_CreateRotationAroundWorldUpVector(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		result.r0c0 = cos(fAmt);
		result.r0c2 = sin(fAmt);
		result.r2c0 = -sin(fAmt);
		result.r2c2 = cos(fAmt);
		return result;
	}

	Matrix3D Matrix3D::_CreateRotationAroundWorldForwardVector(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		result.r0c0 = cos(fAmt);
		result.r0c1 = -sin(fAmt);
		result.r1c0 = sin(fAmt);
		result.r1c1 = cos(fAmt);
		return result;
	}

	Matrix3D Matrix3D::_CreateRotationAroundWorldRightVector(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		result.r1c1 = cos(fAmt);
		result.r1c2 = -sin(fAmt);
		result.r2c1 = sin(fAmt);
		result.r2c2 = cos(fAmt);
		return result;
	}

	Matrix3D Matrix3D::_CreateTranslateAlongWorldUp(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		result._POSITION_Y = fAmt;
		return result;
	}

	Matrix3D Matrix3D::_CreateTranslateAlongWorldForward(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		// Camera space points down negative Z axis
		result._POSITION_Z = -fAmt;
		return result;
	}

	Matrix3D Matrix3D::_CreateTranslateAlongWorldRight(double fAmt) {
		Matrix3D result;
		result._SetIdentityMatrix();
		result._POSITION_X = fAmt;
		return result;
	}

	void Matrix3D::_RotateAroundWorldUpVector(double fAmt) {
		Matrix3D rotate = _CreateRotationAroundWorldUpVector(fAmt);
		Matrix3D result = rotate._Multiply(*this);
		this->_SetEqualTo(result);
	}

	void Matrix3D::_RotateAroundWorldForwardVector(double fAmt) {
		Matrix3D rotate = _CreateRotationAroundWorldForwardVector(fAmt);
		Matrix3D result = rotate._Multiply(*this);
		this->_SetEqualTo(result);
	}

	void Matrix3D::_RotateAroundWorldRightVector(double fAmt) {
		Matrix3D rotate = _CreateRotationAroundWorldRightVector(fAmt);
		Matrix3D result = rotate._Multiply(*this);
		this->_SetEqualTo(result);
	}

	void Matrix3D::_TranslateAlongWorldUp(double fAmt) {
		Matrix3D translate = _CreateTranslateAlongWorldUp(fAmt);
		Matrix3D result = translate._Multiply(*this);
		this->_SetEqualTo(result);
	}

	void Matrix3D::_TranslateAlongWorldForward(double fAmt) {
		Matrix3D translate = _CreateTranslateAlongWorldForward(fAmt);
		Matrix3D result = translate._Multiply(*this);
		this->_SetEqualTo(result);
	}

	void Matrix3D::_TranslateAlongWorldRight(double fAmt) {
		Matrix3D translate = _CreateTranslateAlongWorldRight(fAmt);
		Matrix3D result = translate._Multiply(*this);
		this->_SetEqualTo(result);
	}

}