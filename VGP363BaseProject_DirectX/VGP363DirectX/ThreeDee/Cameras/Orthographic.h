// Orthographic.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Camera.h"
#include "../RayTracer/Misc/Point2D.h"
#include "../RayTracer/Tracers/Whitted.h"
#include "../World/ViewPlane.h"

namespace ThreeD
{
	class _ORTHOGRAPHIC : public _CAMERA
	{
	public:
		_ORTHOGRAPHIC(_WORLD *world);
		_ORTHOGRAPHIC(const _ORTHOGRAPHIC &ph);
		~_ORTHOGRAPHIC();
		_ORTHOGRAPHIC& operator= (const _ORTHOGRAPHIC &ph);

		_RAY _GetDirection(const _POINT2D &p);
		virtual void _RenderScene(int *video, const _WORLD &w);

		_TRACER *tracer_ptr;
	};
}