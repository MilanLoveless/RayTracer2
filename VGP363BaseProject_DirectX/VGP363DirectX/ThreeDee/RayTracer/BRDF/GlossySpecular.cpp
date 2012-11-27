// GlossySpecular.cpp
////////////////////////////////////////////////////////////////////////////////

#include "GlossySpecular.h"

namespace ThreeD
{
	_GLOSSYSPECULAR::_GLOSSYSPECULAR()
		: ks(0.0),
		cs(1.0),
		sampler_ptr(NULL)
	{}
////////////////////////////////////////////////////////////////////////////////
	_GLOSSYSPECULAR::_GLOSSYSPECULAR(const _GLOSSYSPECULAR &glossyspec)
		: ks(glossyspec.ks),
		cs(glossyspec.cs)
	{
		sampler_ptr = glossyspec.sampler_ptr->_Clone();
	}
////////////////////////////////////////////////////////////////////////////////
	_GLOSSYSPECULAR::~_GLOSSYSPECULAR()
	{
		if(sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
	}
////////////////////////////////////////////////////////////////////////////////
	_GLOSSYSPECULAR* _GLOSSYSPECULAR::_Clone()
	{
		return (new _GLOSSYSPECULAR(*this));
	}
////////////////////////////////////////////////////////////////////////////////
	void _GLOSSYSPECULAR::_SetSampler(_SAMPLER *sp, const _DOUBLE exp)
	{
		sampler_ptr = sp;
		sampler_ptr->_MapToHemisphere(exp);
		power = exp;
	}
////////////////////////////////////////////////////////////////////////////////
	void _GLOSSYSPECULAR::_SetSamples(const int ns, const _DOUBLE exp)
	{
		sampler_ptr = new _MULTIJITTERED(ns);
		sampler_ptr->_MapToHemisphere(exp);
	}
////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _GLOSSYSPECULAR::_F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi)
	{
		_COLOR4F L(0.0);
		_DOUBLE ndotwi = wi._DotProduct(wi, sr.normal);
		_VERTEX4F r(((_VERTEX4F(sr.normal) * 2.0 - wi) * ndotwi));
		_DOUBLE rdotwo = r._DotProduct(r, wo);

		if(rdotwo > 0.0)
			L = cs * ks * pow(rdotwo, power);
		return (L);
	}
////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _GLOSSYSPECULAR::_SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf)
	{
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
	_COLOR4F _GLOSSYSPECULAR::_Rho(const _SHADEREC &sr, const _VERTEX4F &wo)
	{
		return _COLOR4F(0.0);
	}
////////////////////////////////////////////////////////////////////////////////
	void _GLOSSYSPECULAR::_SetKS(const _DOUBLE k)
	{
		ks = k;
	}
////////////////////////////////////////////////////////////////////////////////
	void _GLOSSYSPECULAR::_SetPower(const _DOUBLE exp)
	{
		power = exp;
	}
////////////////////////////////////////////////////////////////////////////////
	void _GLOSSYSPECULAR::_SetCS(const _COLOR4F &c)
	{
		cs = c;
	}
}