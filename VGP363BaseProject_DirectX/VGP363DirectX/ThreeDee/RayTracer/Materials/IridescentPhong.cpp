// Phong.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "IridescentPhong.h"

namespace ThreeD
{
	_IRIDESCENTPHONG::_IRIDESCENTPHONG()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		iridescent_brdf(new _IRIDESCENT()),
		specular_brdf(new _GLOSSYSPECULAR())
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.1, 0.9, 0.9));
		ambient_brdf->_SetKA(1.0);
		iridescent_brdf->_SetCD(_COLOR4F(1.0, 0.1, 0.9, 0.9));
		iridescent_brdf->_SetKD(2.0);
		iridescent_brdf->_SetPower(0.5);
		iridescent_brdf->_SetRot(1.0);
		specular_brdf->_SetCS(_COLOR4F(1.0, 1.0, 1.0, 1.0));
		specular_brdf->_SetKS(1.0);
		specular_brdf->_SetPower(30.0);
		specular_brdf->_SetSampler(new _MULTIJITTERED(16), 30.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_IRIDESCENTPHONG::_IRIDESCENTPHONG(const _IRIDESCENTPHONG &mat)
		: _MATERIAL(mat)
	{
		if(mat.ambient_brdf)
			ambient_brdf = mat.ambient_brdf->_Clone();
		else ambient_brdf = NULL;

		if(mat.iridescent_brdf)
			iridescent_brdf = mat.iridescent_brdf->_Clone();
		else iridescent_brdf = NULL;
		
		if(mat.specular_brdf)
			specular_brdf = mat.specular_brdf->_Clone();
		else specular_brdf = NULL;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATERIAL* _IRIDESCENTPHONG::_Clone()
	{
		return (new _IRIDESCENTPHONG(*this));
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_IRIDESCENTPHONG& _IRIDESCENTPHONG::operator= (const _IRIDESCENTPHONG &mat)
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

		if(iridescent_brdf)
		{
			delete iridescent_brdf;
			iridescent_brdf = NULL;
		}

		if(mat.iridescent_brdf)
			iridescent_brdf = mat.iridescent_brdf->_Clone();

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
	_IRIDESCENTPHONG::~_IRIDESCENTPHONG()
	{
		if(ambient_brdf)
		{
			delete ambient_brdf;
			ambient_brdf = NULL;
		}

		if(iridescent_brdf)
		{
			delete iridescent_brdf;
			iridescent_brdf = NULL;
		}

		if(specular_brdf)
		{
			delete specular_brdf;
			specular_brdf = NULL;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _IRIDESCENTPHONG::_Shade(_SHADEREC &sr)
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
					L+= ( iridescent_brdf->_F(sr, wo, wi) + (specular_brdf->_F(sr, wo, wi))) * sr.world_ptr->lights[j]->_L(sr) * ndotwi;
				}
			}
		}
		return L;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENTPHONG::_SetKA(const _DOUBLE k)
	{
		if(ambient_brdf)
			ambient_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENTPHONG::_SetKD(const _DOUBLE k)
	{
		if(iridescent_brdf)
			iridescent_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _IRIDESCENTPHONG::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->_SETCD(c);
		if(iridescent_brdf)
			iridescent_brdf->_SetCD(c);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _IRIDESCENTPHONG::_SetCS(const _COLOR4F &c)
	{
		if(specular_brdf)
			specular_brdf->_SetCS(c);
	}
}