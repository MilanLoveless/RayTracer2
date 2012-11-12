// Phong.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Phong.h"

namespace ThreeD
{
	_PHONG::_PHONG()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		diffuse_brdf(new _LAMBERTIAN()),
		specular_brdf(new _GLOSSYSPECULAR())
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.1, 1.0, 0.3));
		ambient_brdf->_SetKA(1.0);
		diffuse_brdf->_SETCD(_COLOR4F(1.0, 0.1, 1.0, 0.3));
		diffuse_brdf->_SetKD(1.0);
		specular_brdf->_SetCS(_COLOR4F(1.0, 1.0, 1.0, 1.0));
		specular_brdf->_SetKS(1.0);
		specular_brdf->_SetPower(15.0);
		specular_brdf->_SetSampler(new _MULTIJITTERED(16), 15.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_PHONG::_PHONG(const _PHONG &mat)
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
	_MATERIAL* _PHONG::_Clone()
	{
		return (new _PHONG(*this));
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_PHONG& _PHONG::operator= (const _PHONG &mat)
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
	_PHONG::~_PHONG()
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
	_COLOR4F _PHONG::_Shade(_SHADEREC &sr)
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
				L+= (diffuse_brdf->_F(sr, wo, wi)  + specular_brdf->_F(sr, wo, wi)) * sr.world_ptr->lights[j]->_L(sr) * ndotwi;
			}
		}
		return L;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _PHONG::_SetKA(const _DOUBLE k)
	{
		if(ambient_brdf)
			ambient_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _PHONG::_SetKD(const _DOUBLE k)
	{
		if(diffuse_brdf)
			diffuse_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _PHONG::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->_SETCD(c);
		if(diffuse_brdf)
			diffuse_brdf->_SETCD(c);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _PHONG::_SetCS(const _COLOR4F &c)
	{
		if(specular_brdf)
			specular_brdf->_SetCS(c);
	}
}