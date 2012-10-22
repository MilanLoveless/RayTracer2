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

	_COLOR4F _TRACER::_TraceRay(const _RAY &ray, double &maxdraw, _HITINFO &hitinfo)
	{
		bool hiit = false;
		int nobjects = world_ptr->objects.size();
		for(int j=0; j < nobjects; j++)
		{
			hiit = hiit || world_ptr->objects[j]->_Hit(ray, maxdraw, hitinfo);
		}
		if(hiit)
		{
			return hitinfo.hitcolor;
		}
		else return this->world_ptr->backgroundcolor;
	}

	_COLOR4F _TRACER::_TraceRay(const _RAY &ray, double &maxdraw, _HITINFO &hitinfo, int depth)
	{
		if(depth >= world_ptr->maxdepth) return hitinfo.hitcolor;
		depth++;
		int nobjects = world_ptr->objects.size();
		for(int j=0; j < nobjects; j++)
		{
			bool hiit = world_ptr->objects[j]->_Hit(ray, maxdraw, hitinfo);
			if(hiit)
			{
				_RAY refl = hitinfo.normal._Reflect(ray.vector);
				_TraceRay(refl, maxdraw, hitinfo, depth);
			}
		}
	}

}