// Whitted.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Whitted.h"
#include "../../World/World.h"
#include "../Misc/ShadeRec.h"
#include "../Materials/Material.h"

namespace ThreeD
{
	_WHITTED::_WHITTED()
		: _TRACER()
	{}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_WHITTED::_WHITTED(_WORLD *world)
		: _TRACER(world)
	{}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_WHITTED::~_WHITTED() {}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _WHITTED::_TraceRay(const _RAY &ray, const int depth)
	{
		if (depth > world_ptr->maxdepth)
			return(_COLOR4F(0.0));
		else
		{
			_SHADEREC sr(world_ptr->_HitObjects(ray));    
					
			if (sr.hit_an_object)
			{
				sr.depth = depth;
				sr.ray = ray;	
				return (sr.material_ptr->_Shade(sr));   
			}
			else
				return (world_ptr->backgroundcolor);
		}
	}
}