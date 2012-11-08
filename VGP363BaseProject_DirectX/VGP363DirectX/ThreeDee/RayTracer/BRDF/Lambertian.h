// Lambertian.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BRDF.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _LAMBERTIAN : public _BRDF
	{
	public:
		_LAMBERTIAN();
		_LAMBERTIAN(const _LAMBERTIAN &lambert);
		_LAMBERTIAN& operator= (const _LAMBERTIAN &lambert);
		~_LAMBERTIAN();
		virtual _LAMBERTIAN* _Clone();
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo);
		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SETCD(const _COLOR4F c);
		
		_DOUBLE kd;
		_COLOR4F cd;
	};

}