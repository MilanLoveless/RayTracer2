// RayTracer.h
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Constants.h"
#include "../Misc/Ray.h"
#include "../../Components/Color.h"
#include "../Misc/HitInfo.h"


namespace ThreeD
{
	class _WORLD;

	class _TRACER
	{
	public:
		_TRACER(_WORLD *world);
		virtual ~_TRACER();

		virtual _COLOR4F _TraceRay(const _RAY &ray);
		virtual _COLOR4F _TraceRay(const _RAY &ray, int tracedepth);

	private:
		_WORLD *world_ptr;
	};
}