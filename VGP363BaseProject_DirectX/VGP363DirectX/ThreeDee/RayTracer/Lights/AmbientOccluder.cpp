// AmbientOccluder.cpp
/////////////////////////////////////////////////////////////////////

#include "AmbientOccluder.h"
#include "../../World/World.h"

namespace ThreeD
{
	_AMBIENTOCCLUDER::_AMBIENTOCCLUDER()
		: _LIGHT(),
		color(1.0),
		ls(0.1),
		min_amount(0.1),
		u(0.0, 0.0, 0.0, 0.0),
		v(0.0, 0.0, 0.0, 0.0),
		w(0.0, 0.0, 0.0, 0.0),
		sampler_ptr(new _MULTIJITTERED(256))
	{
		sampler_ptr->_MapToHemisphere(1.0);
		shadows = false;
	}
/////////////////////////////////////////////////////////////////////
	_VERTEX4F _AMBIENTOCCLUDER::_GetDirection(_SHADEREC &sr)
	{
		_VERTEX4F sp = sampler_ptr->_SampleHemisphere();
		return (u * sp.x + v * sp.y + w * sp.z); 
	}
/////////////////////////////////////////////////////////////////////
	bool _AMBIENTOCCLUDER::_InShadow(const _RAY &ray, const _SHADEREC &sr)
	{
		float t;
		int num_objects = sr.world_ptr->objects.size();
		
		for(int j = 0; j < num_objects; j++)
		{
			if(sr.world_ptr->objects[j]->_ShadowHit(ray, t))
				return true;
		}
		return false;
	}
/////////////////////////////////////////////////////////////////////
	_COLOR4F _AMBIENTOCCLUDER::_L(_SHADEREC &sr)
	{
		w = sr.normal;
		v = v._CrossProduct(w, _VERTEX4F(0.0072, 1.0, 0.0034, 0.0));
		v._Normalize();
		u = u._CrossProduct(v, w);

		_RAY shadow_ray;
		shadow_ray.origin = sr.hit_point;
		shadow_ray.vector = _GetDirection(sr);

		if (_InShadow(shadow_ray, sr))
			return (color * min_amount * ls);
		else
			return (color * ls);
	}
}