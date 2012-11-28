// AmbientOccluder.h
/////////////////////////////////////////////////////////////////////

#pragma once

#include "Light.h"
#include "../Samplers/Sampler.h"
#include "../Samplers/MultiJittered.h"

namespace ThreeD
{
	class _AMBIENTOCCLUDER : public _LIGHT
	{
	public:
		_AMBIENTOCCLUDER();
		~_AMBIENTOCCLUDER();
		
		void _SetSampler(_SAMPLER *sp);
		virtual _VERTEX4F _GetDirection(_SHADEREC &sr);
		virtual bool _InShadow(const _RAY &ray, const _SHADEREC &sr);
		virtual _COLOR4F _L(_SHADEREC &sr);
		
		_VERTEX4F u, v, w;
		_SAMPLER *sampler_ptr;
		_DOUBLE min_amount;
		_DOUBLE ls;
		_COLOR4F color;
	};
}