// BRDF.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Color.h"
#include "../../Components/Vertex.h"
#include "../../Components/Constants.h"
#include "../../RayTracer/Misc/ShadeRec.h"
#include "../Samplers/Sampler.h"

namespace ThreeD
{
	class _BRDF
	{
	public:
		_BRDF(); 
		_BRDF(const _BRDF &brdf);
		_BRDF& operator= (const _BRDF &brdf);
		~_BRDF();
		
		void _SetSampler(_SAMPLER *s_ptr);
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo, float &pdf);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo) = 0;

		_SAMPLER *sampler_ptr;
	};

}