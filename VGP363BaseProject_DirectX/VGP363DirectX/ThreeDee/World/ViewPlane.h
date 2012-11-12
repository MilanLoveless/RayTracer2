// ViewPlane.h
/////////////////////////////////////////////////

#pragma once

#include "../RayTracer/Samplers/Sampler.h"
#include "../RayTracer/Samplers/MultiJittered.h"
#include "../RayTracer/Samplers/Regular.h"
#include "../Components/Constants.h"
#include "../RayTracer/Samplers/Hammersley.h"

namespace ThreeD
{
	class _VIEWPLANE
	{
	public:
		int hres, vres;
		_DOUBLE s;
		int num_samples;

		_SAMPLER *sampler_ptr;
		_DOUBLE gamma, inv_gamma;
		bool show_out_of_gammut;

		_VIEWPLANE();
		_VIEWPLANE(const _VIEWPLANE &vp);
		_VIEWPLANE& operator= (const _VIEWPLANE &vp);
		~_VIEWPLANE();

		void _SetHRes(const int h);
		void _SetVRes(const int v);
		void _SetPixelSize(const _DOUBLE size);
		void _SetGamma(const _DOUBLE g);
		void _SetSamples(const int n);
		void _SetSampler(_SAMPLER *sp);
	};
}