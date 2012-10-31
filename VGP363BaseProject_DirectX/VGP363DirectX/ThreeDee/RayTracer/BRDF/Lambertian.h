// Lambertian.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BRDF.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _LAMBERTIAN : public BRDF
	{
	public:
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wi, _VERTEX4F &wo);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo);

		double kd;
		_COLOR4F cd;
	};

}