// Pinhole.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Pinhole.h"
#include "../World/ViewPlane.h"

namespace ThreeD
{
	void _PINHOLE::_SetFOV(const _DOUBLE fov)
	{
		d = (0.5/(tan(fov*0.5)));
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void _PINHOLE::_SetZoom(_DOUBLE zooom)
	{
		zoom = zooom;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_PINHOLE& _PINHOLE::operator= (const _PINHOLE &ph)
	{
		if(this == &ph)
			return (*this);
		_CAMERA::operator=(ph);
		d = ph.d;
		zoom = ph.zoom;
		return (*this);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_PINHOLE::~_PINHOLE()
	{

	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_RAY _PINHOLE::_GetDirection(const _POINT2D &p)
	{
		_VERTEX4F dir = transformM16._Multiply(_VERTEX4F(p.x, p.y, 0.0, 1.0)-_VERTEX4F(0.0, 0.0, -d, 1.0));
		dir._Normalize();
		_VERTEX4F orig = transformM16._Multiply(iposition);
		return _RAY(orig, dir);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void _PINHOLE::_RenderScene(const _WORLD &w)
	{
		_COLOR4F L;
		_VIEWPLANE vp(w.vp);
		_RAY ray;
		int depth = 0;
		_POINT2D p2d;
		int n = (int)sqrt((float)vp.num_samples);
		vp.s /= zoom;
		
		for(int v = 0; v < vp.vres; v++)
		{
			for(int u = 0; u < vp.hres; u++)
			{
	}
}