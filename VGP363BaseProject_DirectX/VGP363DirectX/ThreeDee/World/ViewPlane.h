// ViewPlane.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Components/Constants.h"
#include "../RayTracer/Samplers/Sampler.h"

namespace ThreeD
{
	class _VIEWPLANE
	{
		int hres, vres;
		_DOUBLE s;
		_DOUBLE gamma, inv_gamma;
		int num_samples;
		_SAMPLER *sampler_ptr;

		void _SetSampler(_SAMPLER *sp);
		void _SetSamples(const int n);

	};
}