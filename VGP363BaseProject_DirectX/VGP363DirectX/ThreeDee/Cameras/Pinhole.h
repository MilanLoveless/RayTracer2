// Pinhole.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Camera.h"
#include "../RayTracer/Misc/Point2D.h"
#include "../RayTracer/Tracers/Whitted.h"
#include "../World/ViewPlane.h"
#include "../../CORE/CORE.Drawing.h"

namespace ThreeD
{
	class _PINHOLE : public _CAMERA
	{
	public:
		_PINHOLE();
		_PINHOLE(const _PINHOLE &ph);
		~_PINHOLE();
		_PINHOLE& operator= (const _PINHOLE &ph);

		void _SetFOV(const _DOUBLE fov);
		void _SetZoom(const _DOUBLE zooom);
		_RAY _GetDirection(const _POINT2D &p);
		virtual void _RenderScene(int *video, const _WORLD &w);

		_DOUBLE d;
		_DOUBLE zoom;
		_TRACER *tracer_ptr;
	};
}