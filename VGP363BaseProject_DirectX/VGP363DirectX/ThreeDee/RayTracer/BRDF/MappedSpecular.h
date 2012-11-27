// MappedSpecular.h
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BRDF.h"
#include "../../../CORE/CORE.Hardware.3D.Texture.h"
#include "../Samplers/MultiJittered.h"

namespace ThreeD
{
	class _MAPPEDSPECULAR : public _BRDF
	{
	public:
		_MAPPEDSPECULAR();
		_MAPPEDSPECULAR(const _MAPPEDSPECULAR &mspecular);
		~_MAPPEDSPECULAR();
		virtual _MAPPEDSPECULAR* _Clone();
		
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo);

		void _SetKS(const _DOUBLE k);
		void _SetPower(const _DOUBLE exp);
		void _SetCS(const _COLOR4F &c);
		void _SetSampler(_SAMPLER *sp, const _DOUBLE exp);
		void _SetSamples(const int ns, const _DOUBLE exp);
		void _CalculateCS(const _POINT2D &uv);
		
		_DOUBLE ks;
		_DOUBLE power;
		_COLOR4F cs;
		_SAMPLER *sampler_ptr;
		CORE::HARDWARE::TEXTUREINFO *specular_map;
	};
}