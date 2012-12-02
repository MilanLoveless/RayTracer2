// Lambertian.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MappedLambert.h"

namespace ThreeD
{
	_MAPPEDLAMBERT::_MAPPEDLAMBERT()
		: _BRDF(),
		kd(0.0),
		cd(0.0),
		diffuse_map(NULL)
	{}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDLAMBERT::_MAPPEDLAMBERT(const _MAPPEDLAMBERT &lambert)
		:_BRDF(lambert),
		kd(lambert.kd),
		cd(lambert.cd),
		diffuse_map(lambert.diffuse_map)
	{}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDLAMBERT& _MAPPEDLAMBERT::operator= (const _MAPPEDLAMBERT &lambert)
	{
		if(this == &lambert)
			return (*this);
		
		kd = lambert.kd;
		cd = lambert.cd;
		diffuse_map = lambert.diffuse_map;
		return(*this);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDLAMBERT::~_MAPPEDLAMBERT() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDLAMBERT* _MAPPEDLAMBERT::_Clone()
	{
		return (new _MAPPEDLAMBERT(*this));
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MAPPEDLAMBERT::_SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf)
	{
		_CalculateCD(sr.hit_UV);
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
	_COLOR4F _MAPPEDLAMBERT::_F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo)
	{
		_CalculateCD(sr.hit_UV);
		return (cd * kd * INV_PI);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MAPPEDLAMBERT::_Rho(const _SHADEREC &sr, const _VERTEX4F &wo)
	{
		_CalculateCD(sr.hit_UV);
		return (cd * kd);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDLAMBERT::_SetCD(const _COLOR4F c)
	{
		cd = c;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDLAMBERT::_SetKA(_DOUBLE k)
	{
		kd = k;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDLAMBERT::_SetKD(_DOUBLE k)
	{
		kd = k;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDLAMBERT::_CalculateCD(const _POINT2D &uv)
	{
		CORE::HARDWARE::_LockTexture(diffuse_map);
		if(diffuse_map->_video != NULL)
			{
				int n = GetPixel(diffuse_map->_video, diffuse_map->_nWidth, diffuse_map->_nHeight, (int)((fmod(uv.x, 1)) * diffuse_map->_nWidth), (int)((1.0 - fmod(uv.y, 1)) * diffuse_map->_nHeight));
				cd = _COLOR4F(1.0, (_COLOR32_ARGB_GET_RED(n))/255.0, (_COLOR32_ARGB_GET_GREEN(n))/255.0, (_COLOR32_ARGB_GET_BLUE(n))/255.0);
			}
		CORE::HARDWARE::_UnlockTexture(diffuse_map);
	}
}