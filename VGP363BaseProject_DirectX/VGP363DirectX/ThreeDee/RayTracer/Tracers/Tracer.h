// Tracer.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../Components/Constants.h"
#include "../Misc/Ray.h"
#include "../../Components/Color.h"
#include "../../World/World.h"

#pragma once

namespace ThreeD
{
	class _TRACER
	{
	public:
		_TRACER();
		_TRACER(_WORLD *world);
		~_TRACER();
		
		virtual _COLOR4F _TraceRay(const _RAY &ray, const int depth) = 0;

		_WORLD *world_ptr;
	};
}