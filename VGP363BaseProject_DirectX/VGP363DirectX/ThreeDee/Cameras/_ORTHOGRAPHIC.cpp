// ORTHOGRAPHIC.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ORTHOGRAPHIC.h"


namespace ThreeD
{
	_ORTHOGRAPHIC::_ORTHOGRAPHIC(_WORLD *world)
		:_CAMERA()
	{
		tracer_ptr = new _WHITTED(world);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_ORTHOGRAPHIC& _ORTHOGRAPHIC::operator= (const _ORTHOGRAPHIC &ph)
	{
		if(this == &ph)
			return (*this);
		_CAMERA::operator=(ph);
		return (*this);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_ORTHOGRAPHIC::~_ORTHOGRAPHIC()
	{
		if(tracer_ptr)
		{
			delete tracer_ptr;
			tracer_ptr = NULL;
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_RAY _ORTHOGRAPHIC::_GetDirection(const _POINT2D &p)
	{
		_VERTEX4F dir = _VERTEX4F(0.0, 0.0, 1.0, 0.0);
		//dir._Normalize();
		_VERTEX4F orig = _VERTEX4F(p.x, p.y, 0.0, 1.0);
		return _RAY(orig, dir);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void _ORTHOGRAPHIC::_RenderScene(int *video, const _WORLD &w)
	{
		_COLOR4F L;
		_RAY ray;
		int depth = 0;
		_POINT2D sp;
		_POINT2D pp;
		
		for(int y = 0; y < w.vp.vres; y++)
		{
			for(int x = 0; x < w.vp.hres; x++)
			{
				L = _COLOR4F(0.0);
				pp.x = x - w.vp.hres/2.0;
				pp.y = -y + w.vp.vres/2.0;

				ray = _GetDirection(pp);
				L = tracer_ptr->_TraceRay(ray, depth);
				L._Normalize();

				int color = CreateColor(255, (int)(L.r*255.0), (int)(L.g*255.0), (int)(L.b*255.0));
				
				PutPixel(video, w.vp.hres, w.vp.vres, x, y, color);
			}
		}
	}
}