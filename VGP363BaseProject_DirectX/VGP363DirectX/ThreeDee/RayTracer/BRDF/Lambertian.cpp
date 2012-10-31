// Lambertian.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lambertian.h"

namespace ThreeD
{
	_COLOR4F _LAMBERTIAN::_F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo)
	{
		return (cd * kd * INV_PI);
	}

	_COLOR4F _LAMBERTIAN::_Rho(const _SHADEREC &sr, const _VERTEX4F &wo)
	{
		return (cd * kd);
	}

}