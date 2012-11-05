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
		if (depth > world_ptr->vp.max_depth)
			return(_COLOR4F(0.0));
		else {
			_SHADEREC sr(world_ptr->hit_objects(ray));    
					
			if (sr.hit_an_object) {
				sr.depth = depth;
				sr.ray = ray;	
				return (sr.material_ptr->shade(sr));   
			}
			else
				return (world_ptr->background_color);
		}	
}