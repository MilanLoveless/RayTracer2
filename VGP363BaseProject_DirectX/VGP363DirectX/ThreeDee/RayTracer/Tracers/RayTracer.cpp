#include "RayTracer.h"

namespace ThreeD
{
	_TRACER::_TRACER(_WORLD *world)
	{
		world_ptr = world;
	}

	_TRACER::~_TRACER(void) {
		if (world_ptr)
			world_ptr = NULL;
	}

	_COLOR4F _TRACER::_TraceRay(const _RAY &ray)
	{
		return _COLOR4F(0.25);
	}

	_COLOR4F _TRACER::_TraceRay(const _RAY &ray, const int depth) {
		return _COLOR4F(0.25);
	}

}