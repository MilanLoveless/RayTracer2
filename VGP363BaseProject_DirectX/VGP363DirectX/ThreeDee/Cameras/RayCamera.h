//Camera.h
///////////////////////////////////////////////////////////
#pragma once
#include "../Components/Vertex.h"
#include "../Components/Matrix.h"
#include "../RayTracer/Misc/Ray.h"

namespace ThreeD
{
	class RayCamera
	{
	public:
		_VERTEX4F m_v4fPosition, m_v4fFocalPoint;
		double m_dFocalLength, m_dStepSize, m_dWidth, m_dHeight;
		int m_iWidth, m_iHeight, m_iFOVAngle;
		_MATRIX16F m_m16fCameraMatrix;
		RayCamera();
		void _Initialize(int w, int h, int angle);
		_RAY _CreateRay(int x, int y);
	};
}	