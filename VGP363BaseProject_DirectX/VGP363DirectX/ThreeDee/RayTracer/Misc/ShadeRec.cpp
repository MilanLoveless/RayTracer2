// ShadeRec.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ShadeRec.h"
#include "../../World/World.h"

namespace ThreeD
{
	_SHADEREC::_SHADEREC(_WORLD &w)
	{
		t = kHugeValue;
		hit_an_object = false;
		material_ptr = NULL;
		hit_UV = _POINT2D(0.0, 0.0);
		hit_point = _VERTEX4F(0.0, 0.0, 0.0, 0.0);
		local_hit_point = _VERTEX4F(0.0, 0.0, 0.0, 0.0);
		normal = _VERTEX4F(0.0, 0.0, 0.0, 0.0);
		color = _COLOR4F(0.0);
		ray = _RAY(_VERTEX4F(0.0, 0.0, 0.0, 1.0),_VERTEX4F(0.0, 0.0, 0.0, 0.0));
		depth = 0;
		light_dir = _VERTEX4F(0.0, 0.0, 0.0, 0.0);
		world_ptr = &w;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		_SHADEREC::_SHADEREC(const _SHADEREC &sr)
	{
		t = sr.t;
		hit_an_object = sr.hit_an_object;
		material_ptr = sr.material_ptr;
		hit_UV = sr.hit_UV;
		hit_point = sr.hit_point;
		local_hit_point = sr.local_hit_point;
		normal = sr.normal;
		color = sr.color;
		ray = sr.ray;
		depth = sr.depth;
		light_dir = sr.light_dir;
		world_ptr = sr.world_ptr;
	}
}