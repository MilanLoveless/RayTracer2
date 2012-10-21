// RayTracer.h
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Constants.h"
#include "../Misc/Ray.h"
#include "../../Components/Color.h"
#include "../Misc/HitInfo.h"
#include "../../World/World.h"
#include "../Misc/HitInfo.h"

namespace ThreeD
{
	class _TRACER
	{
	public:
		_TRACER(_WORLD *world);
		virtual ~_TRACER();

		virtual _COLOR4F _TraceRay(const _RAY &ray, double &maxdraw, _HITINFO &hitinfo);
		virtual _COLOR4F _TraceRay(const _RAY &ray, double &maxdraw, _HITINFO &hitinfo, int tracedepth);

	protected:
		_WORLD *world_ptr;
	};
}