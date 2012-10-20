// RayCamera.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RayCamera.h"

namespace ThreeD
{

	RayCamera::RayCamera()
	{
		this->m_m16fCameraMatrix._SetToIdentity();
		this->m_iWidth = 1920;
		this->m_iHeight = 1080;
		this->m_iFOVAngle = 60;
		this->m_dFocalLength = sqrt(3.0)/2.0;
		this->m_dWidth = 1.0;
		this->m_dStepSize = this->m_dWidth/(double)m_iWidth;
		this->m_dHeight = this->m_dStepSize*(double)m_iHeight;
		this->m_v4fPosition = _VERTEX4F(0.0, 0.0, 0.0, 1.0);
		this->m_v4fFocalPoint = _VERTEX4F(0.0, 0.0, -1.0*this->m_dFocalLength, 1.0);
	}

	void RayCamera::_Initialize(int w, int h, int angle)
	{
		this->m_iWidth = w;
		this->m_iHeight = h;
		this->m_iFOVAngle;
		this->m_dFocalLength = this->m_dWidth/tan(((double)this->m_iFOVAngle/180.0)*3.14159265359);
		this->m_dWidth = 1.0;
		this->m_dStepSize = this->m_dWidth/(double)m_iWidth;
		this->m_dHeight = this->m_dStepSize*(double)m_iHeight;
		this->m_v4fFocalPoint = _VERTEX4F(0.0, 0.0, -1.0*this->m_dFocalLength, 1.0);
	}

	_RAY RayCamera::_CreateRay(int x, int y)
	{
		x=x+1;
		y=y+1;
		_VERTEX4F RayVector = _VERTEX4F(((double)x*this->m_dStepSize)-(0.5*this->m_dWidth-(0.5*this->m_dStepSize)), ((double)y*this->m_dStepSize)-(0.5*this->m_dHeight-(0.5*this->m_dStepSize)), 0.0, 1.0) - this->m_v4fFocalPoint;
		RayVector = m_m16fCameraMatrix._Multiply(RayVector);
		RayVector._Normalize();
		_RAY CameraRay = _RAY(this->m_v4fFocalPoint, RayVector);
		return CameraRay;
	}

}