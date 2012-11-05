// Camera.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Camera.h"

namespace ThreeD
{
	_CAMERA::_CAMERA()
		: iposition(0.0, 0.0, -500.0, 1.0),
		  ifacing(0.0, 0.0, 1.0, 1.0),
		  transformM16(_VERTEX4F(1.0, 0.0, 0.0, 0.0),
					   _VERTEX4F(0.0, 1.0, 0.0, 0.0),
					   _VERTEX4F(0.0, 0.0, 1.0, 0.0),
					   _VERTEX4F(0.0, 0.0, 0.0, 1.0)),
		  exposure_time(1.0)
	{}

	_CAMERA::_CAMERA(const _CAMERA &c)
		: iposition(c.iposition),
		  ifacing(c.ifacing),
		  transformM16(c.transformM16),
		  exposure_time(c.exposure_time)
	{}
		
	_CAMERA::~_CAMERA()
	{

	}

	void _CAMERA::_SetPos(const _VERTEX4F &p)
	{
		iposition = p;
	}

	void _CAMERA::_SetPos(const _DOUBLE x1, const _DOUBLE y1, const _DOUBLE z1)
	{
		iposition = _VERTEX4F(x1, y1, z1, 1.0);
	}
		
	void _CAMERA::_SetMatrix(const _MATRIX16F &m1)
	{
		transformM16 = m1;
	}

	void _CAMERA::_SetExposure(const _DOUBLE exp1)
	{
		exposure_time = exp1;
	}
		
	_CAMERA& _CAMERA::operator= (const _CAMERA &c)
	{
		if(this == &c)
			return (*this);

		iposition = c.iposition;
		ifacing = c.ifacing;
		transformM16 = c.transformM16;
		exposure_time = c.exposure_time;

		return (*this);
	}
}