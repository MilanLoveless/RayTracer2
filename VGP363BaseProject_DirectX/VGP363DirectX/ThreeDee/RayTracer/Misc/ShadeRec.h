// ShadeRec.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Color.h"
#include "../Misc/Ray.h"
//#include "../../World/World.h"
#include "../Materials/Material.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _WORLD;

	class _SHADEREC
	{
	public:
		_SHADEREC(_WORLD &w);
		_SHADEREC(const _SHADEREC &sr);

		_DOUBLE t;
		bool hit_an_object;
		_MATERIAL *material_ptr;
		_VERTEX4F hit_point;
		_VERTEX4F local_hit_point;
		_VERTEX4F normal;
		_COLOR4F color;
		_RAY ray;
		int depth;
		_VERTEX4F light_dir;
		_WORLD *world_ptr;
	};
}