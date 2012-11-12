// Phong.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "IridescentPhong.h"

namespace ThreeD
{
	_IRIDESCENT::_IRIDESCENT()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		diffuse_brdf(new _LAMBERTIAN()),
		specular_brdf(new _GLOSSYSPECULAR())
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.1, 0.9, 0.9));
		ambient_brdf->_SetKA(1.0);
		diffuse_brdf->_SETCD(ambient_brdf->cd);
		diffuse_brdf->_SetKD(1.0);
		specular_brdf->_SetCS(_COLOR4F(1.0, 1.0, 1.0, 1.0));
		specular_brdf->_SetKS(1.0);
		specular_brdf->_SetPower(30.0);
		specular_brdf->_SetSampler(new _MULTIJITTERED(16), 30.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_IRIDESCENT::_IRIDESCENT(const _IRIDESCENT &mat)
		: _MATERIAL(mat)
	{
		if(mat.ambient_brdf)
			ambient_brdf = mat.ambient_brdf->_Clone();
		else ambient_brdf = NULL;

		if(mat.diffuse_brdf)
			diffuse_brdf = mat.diffuse_brdf->_Clone();
		else diffuse_brdf = NULL;
		
		if(mat.specular_brdf)
			specular_brdf = mat.specular_brdf->_Clone();
		else specular_brdf = NULL;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATERIAL* _IRIDESCENT::_Clone()
	{
		return (new _IRIDESCENT(*this));
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_IRIDESCENT& _IRIDESCENT::operator= (const _IRIDESCENT &mat)
	{
		if(this == &mat)
			return(*this);
		_MATERIAL::operator=(mat);

		if(ambient_brdf)
		{
			delete ambient_brdf;
			ambient_brdf = NULL;
		}

		if(mat.ambient_brdf)
			ambient_brdf = mat.ambient_brdf->_Clone();

		if(diffuse_brdf)
		{
			delete diffuse_brdf;
			diffuse_brdf = NULL;
		}

		if(mat.diffuse_brdf)
			diffuse_brdf = mat.diffuse_brdf->_Clone();

		if(specular_brdf)
		{
			delete specular_brdf;
			specular_brdf = NULL;
		}

		if(mat.specular_brdf)
			specular_brdf = mat.specular_brdf->_Clone();

		return (*this);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_IRIDESCENT::~_IRIDESCENT()
	{
		if(ambient_brdf)
		{
			delete ambient_brdf;
			ambient_brdf = NULL;
		}

		if(diffuse_brdf)
		{
			delete diffuse_brdf;
			diffuse_brdf = NULL;
		}

		if(specular_brdf)
		{
			delete specular_brdf;
			specular_brdf = NULL;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _IRIDESCENT::_Shade(_SHADEREC &sr)
	{
		_VERTEX4F wo = sr.ray.vector * -1.0;
		_COLOR4F L = ambient_brdf->_Rho(sr, wo) * sr.world_ptr->ambient_ptr->_L(sr);
		int num_lights = sr.world_ptr->lights.size();

		for (int j = 0; j < num_lights; j++)
		{
			_VERTEX4F wi = sr.world_ptr->lights[j]->_GetDirection(sr);
			_DOUBLE ndotwi = wi._DotProduct(sr.normal, wi);
			
			if(ndotwi > 0.0)
			{
				bool in_shadow = false;
				if(sr.world_ptr->lights[j]->shadows)
				{
					_RAY shadow_ray(sr.hit_point, wi);
					in_shadow = sr.world_ptr->lights[j]->_InShadow(shadow_ray, sr);
				}
				if(!in_shadow)
				{
					_DOUBLE ndotwo = 1.0 - sr.normal._DotProduct(sr.normal, wo);
					_COLOR4F iridescent = (diffuse_brdf->_F(sr, wo, wi));
					_VERTEX4F v(iridescent.r, iridescent.g, iridescent.b, 0.0);
					_VERTEX4F k(1.0, 1.0, 1.0, 0.0);
					k._Normalize();
					ndotwo = pow((double)ndotwo, 0.5);
					_VERTEX4F v1 = (v * cos(-1.0*ndotwo*PI) + k._CrossProduct(k, v)*sin(-1.0*ndotwo*PI) + k * k._DotProduct(k, v) * (1.0 - cos(-1.0*ndotwo*PI)));
					_COLOR4F iridescent1 = _COLOR4F(1.0, v1.x, v1.y, v1.z);
					L+= ( iridescent1 + (specular_brdf->_F(sr, wo, wi)*iridescent1)) * sr.world_ptr->lights[j]->_L(sr) * ndotwi;
				}
			}
		}
		return L;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENT::_SetKA(const _DOUBLE k)
	{
		if(ambient_brdf)
			ambient_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENT::_SetKD(const _DOUBLE k)
	{
		if(diffuse_brdf)
			diffuse_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENT::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->_SETCD(c);
		if(diffuse_brdf)
			diffuse_brdf->_SETCD(c);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _IRIDESCENT::_SetCS(const _COLOR4F &c)
	{
		if(specular_brdf)
			specular_brdf->_SetCS(c);
	}
}