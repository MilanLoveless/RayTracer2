// Lambertian.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lambertian.h"

namespace ThreeD
{
	_LAMBERTIAN::_LAMBERTIAN()
		: _BRDF(),
		kd(0.0),
		cd(0.0)
	{}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_LAMBERTIAN::_LAMBERTIAN(const _LAMBERTIAN &lambert)
		:_BRDF(lambert),
		kd(lambert.kd),
		cd(lambert.cd)
	{}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_LAMBERTIAN& _LAMBERTIAN::operator= (const _LAMBERTIAN &lambert)
	{
		if(this == &lambert)
			return (*this);
		
		kd = lambert.kd;
		cd = lambert.cd;

		return(*this);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_LAMBERTIAN::~_LAMBERTIAN() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_LAMBERTIAN* _LAMBERTIAN::_Clone()
	{
		return (new _LAMBERTIAN(*this));
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _LAMBERTIAN::_SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf)
	{
		_VERTEX4F w = sr.normal;
		_VERTEX4F v = w._CrossProduct(_VERTEX4F(0.0034, 1.0, 0.0071, 0.0), w);
		v._Normalize();
		_VERTEX4F u = w._CrossProduct(v, w);

		_VERTEX4F sp = sampler_ptr->_SampleHemisphere();
		wi = u * sp.x + v * sp.y + w * sp.z;
		wi._Normalize();

		pdf = wi._DotProduct(sr.normal, wi) * INV_PI;

		return (cd * kd * INV_PI);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _LAMBERTIAN::_F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo)
	{
		return (cd * kd * INV_PI);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _LAMBERTIAN::_Rho(const _SHADEREC &sr, const _VERTEX4F &wo)
	{
		return (cd * kd);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _LAMBERTIAN::_SETCD(const _COLOR4F c)
	{
		cd = c;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _LAMBERTIAN::_SetKA(_DOUBLE k)
	{
		kd = k;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _LAMBERTIAN::_SetKD(_DOUBLE k)
	{
		kd = k;
	}
}