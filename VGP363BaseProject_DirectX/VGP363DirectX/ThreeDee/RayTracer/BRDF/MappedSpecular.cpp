// MappedSpecular.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MappedSpecular.h"

namespace ThreeD
{
	_MAPPEDSPECULAR::_MAPPEDSPECULAR()
		: ks(0.0),
		cs(1.0),
		power(1.0),
		sampler_ptr(NULL),
		specular_map(NULL)
	{}
////////////////////////////////////////////////////////////////////////////////
	_MAPPEDSPECULAR::_MAPPEDSPECULAR(const _MAPPEDSPECULAR &mspecular)
		: ks(mspecular.ks),
		cs(mspecular.cs),
		power(mspecular.power),
		specular_map(mspecular.specular_map)
	{
		sampler_ptr = mspecular.sampler_ptr->_Clone();
		sampler_ptr->_MapToHemisphere(power);
	}
////////////////////////////////////////////////////////////////////////////////
	_MAPPEDSPECULAR::~_MAPPEDSPECULAR()
	{
		if(sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
	}
////////////////////////////////////////////////////////////////////////////////
	_MAPPEDSPECULAR* _MAPPEDSPECULAR::_Clone()
	{
		return (new _MAPPEDSPECULAR(*this));
	}
////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDSPECULAR::_SetSampler(_SAMPLER *sp, const _DOUBLE exp)
	{
		sampler_ptr = sp;
		sampler_ptr->_MapToHemisphere(exp);
		power = exp;
	}
////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDSPECULAR::_SetSamples(const int ns, const _DOUBLE exp)
	{
		sampler_ptr = new _MULTIJITTERED(ns);
		sampler_ptr->_MapToHemisphere(exp);
	}
////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MAPPEDSPECULAR::_F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi)
	{
		_CalculateCS(sr.hit_UV);
		_COLOR4F L(0.0);
		_DOUBLE ndotwi = wi._DotProduct(wi, sr.normal);
		_VERTEX4F r(((_VERTEX4F(sr.normal) * 2.0 - wi) * ndotwi));
		_DOUBLE rdotwo = r._DotProduct(r, wo);

		if(rdotwo > 0.0)
			L = cs * ks * pow(rdotwo, power);
		return (L);
	}
////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MAPPEDSPECULAR::_SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf)
	{
		_CalculateCS(sr.hit_UV);
		_DOUBLE ndotwo = wo._DotProduct(wo, sr.normal);
		_VERTEX4F r = _VERTEX4F(wo) * -1.0 + _VERTEX4F(sr.normal) * 2.0 * ndotwo;

		_VERTEX4F u = r._CrossProduct(_VERTEX4F(0.00424, 1, 0.00764, 0.0), r);
		_VERTEX4F v = r._CrossProduct(u, r);

		_VERTEX4F sp = sampler_ptr->_SampleHemisphere();
		wi = u * sp.x + v * sp.y + r * sp.z;

		float phong_lobe = pow(wi._DotProduct(r, wi), power);
		pdf = phong_lobe * wi._DotProduct(sr.normal, wi);

		return (cs * ks * phong_lobe);
	}
////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MAPPEDSPECULAR::_Rho(const _SHADEREC &sr, const _VERTEX4F &wo)
	{
		return _COLOR4F(0.0);
	}
////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDSPECULAR::_SetKS(const _DOUBLE k)
	{
		ks = k;
	}
////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDSPECULAR::_SetPower(const _DOUBLE exp)
	{
		power = exp;
	}
////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDSPECULAR::_SetCS(const _COLOR4F &c)
	{
		cs = c;
	}

	void _MAPPEDSPECULAR::_CalculateCS(const _POINT2D &uv)
	{
		CORE::HARDWARE::_LockTexture(specular_map);
		if(specular_map->_video != NULL)
			{
				int n = GetPixel(specular_map->_video, specular_map->_nWidth, specular_map->_nHeight, (int)((1.0 - fmod(uv.x, 1)) * specular_map->_nWidth), (int)((1.0 - fmod(uv.y, 1)) * specular_map->_nHeight));
				cs = _COLOR4F(1.0, (_COLOR32_ARGB_GET_RED(n))/255.0, (_COLOR32_ARGB_GET_GREEN(n))/255.0, (_COLOR32_ARGB_GET_BLUE(n))/255.0);
			}
		CORE::HARDWARE::_UnlockTexture(specular_map);
	}
}