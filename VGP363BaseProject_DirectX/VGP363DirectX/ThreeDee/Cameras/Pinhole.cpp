// Pinhole.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Pinhole.h"


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
		_VERTEX4F dir = transformM16._Multiply(_VERTEX4F(p.x, p.y, d, 1.0));
		dir._Normalize();
		_VERTEX4F orig = transformM16._Multiply(iposition);
		return _RAY(orig, dir);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void _PINHOLE::_RenderScene(int *video, const _WORLD &w)
	{
		_COLOR4F L;
		_RAY ray;
		int depth = 0;
		_POINT2D sp;
		_POINT2D pp;
		
		for(int v = 0; v < w.vp.vres; v++)
		{
			for(int u = 0; u < w.vp.hres; u++)
			{
				L = _COLOR4F(0.0);
				for(int j = 0; j < w.vp.num_samples; j++)
				{
					sp = w.vp.sampler_ptr->_SampleSquare();
					pp.x = w.vp.s * (u - 0.5 * w.vp.hres + sp.x);
					pp.y = w.vp.s * (v - 0.5 * w.vp.vres + sp.y);
					ray = _GetDirection(pp);
					L += tracer_ptr->_TraceRay(ray, depth);
				}
				
				L /= w.vp.num_samples;
				L *= exposure_time;

				L._Normalize();
				int color = CreateColor(1.0, (int)(L.r*255.0), (int)(L.g*255.0), (int)(L.b*255.0));
				
				PutPixel(video, w.vp.hres, w.vp.vres, u, v, color);
			}
		}
	}
}