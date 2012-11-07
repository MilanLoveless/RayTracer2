// ViewPlane.h
/////////////////////////////////////////////////

#pragma once

#include "../RayTracer/Samplers/Sampler.h"

namespace ThreeD
{
	class _VIEWPLANE
	{
	public:
		int hres, vres;
		float s;
		int num_samples;

		_SAMPLER *sampler;
		float gamma, inv_gamma;
		//bool show_out_of_gammut;

		_VIEWPLANE();
		_VIEWPLANE(const _VIEWPLANE &vp);
		_VIEWPLANE operator= (const _VIEWPLANE &vp);
		~_VIEWPLANE();

		void _SetHRes(const int h);
		void _SetVRes(const int v);
		void _SetPixelSize(const float size);
		void _SetGamma(const float g);
		void _SetSamples(const int n);
	};
}