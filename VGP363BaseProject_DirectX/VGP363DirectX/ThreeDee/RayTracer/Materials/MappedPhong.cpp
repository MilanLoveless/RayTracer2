// MappedPhong.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MappedPhong.h"

namespace ThreeD
{
	_MAPPEDPHONG::_MAPPEDPHONG()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		diffuse_brdf(new _MAPPEDLAMBERT()),
		specular_brdf(new _MAPPEDSPECULAR()),
		normal_map(NULL)
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.1, 0.1, 0.2));
		ambient_brdf->_SetKA(0.5);
		diffuse_brdf->_SetCD(_COLOR4F(1.0, 0.9, 0.3, 0.5));
		diffuse_brdf->_SetKD(1.0);
		specular_brdf->_SetCS(_COLOR4F(1.0, 1.0, 1.0, 1.0));
		specular_brdf->_SetKS(0.7);
		specular_brdf->_SetSampler(new _MULTIJITTERED(16), 3.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDPHONG::_MAPPEDPHONG(const _MAPPEDPHONG &mat)
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
		
		if(mat.normal_map)
			normal_map = mat.normal_map;
		else normal_map = NULL;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATERIAL* _MAPPEDPHONG::_Clone()
	{
		return (new _MAPPEDPHONG(*this));
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDPHONG& _MAPPEDPHONG::operator= (const _MAPPEDPHONG &mat)
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
	_MAPPEDPHONG::~_MAPPEDPHONG()
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
	_COLOR4F _MAPPEDPHONG::_Shade(_SHADEREC &sr)
	{
		_VERTEX4F wo = sr.ray.vector * -1.0;
				
		CORE::HARDWARE::_LockTexture(normal_map);
		if(normal_map->_video != NULL)
			{
				int n = GetPixel(normal_map->_video, normal_map->_nWidth, normal_map->_nHeight, (int)((fmod(sr.hit_UV.x, 1)) * normal_map->_nWidth), (int)((1.0 -fmod(sr.hit_UV.y, 1)) * normal_map->_nHeight));
				_MATRIX16F orthoTS( sr.tangent, sr.normal, sr.binormal, _VERTEX4F(0.0, 0.0, 0.0, 1.0));
				_VERTEX4F nrmap(-1.0 * (_COLOR32_ARGB_GET_RED(n)/127.5 - 1.0), (_COLOR32_ARGB_GET_BLUE(n)/255.0), (_COLOR32_ARGB_GET_GREEN(n)/127.5 - 1.0), 0.0);
				sr.normal = orthoTS._Multiply(nrmap);
				sr.normal._Normalize();
			}
		CORE::HARDWARE::_UnlockTexture(normal_map);

		_COLOR4F L = diffuse_brdf->_Rho(sr, wo) * 0.5;  //sr.world_ptr->ambient_ptr->_L(sr);
		//_COLOR4F ao = L;

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
	void _MAPPEDPHONG::_SetKA(const _DOUBLE k)
	{
		if(ambient_brdf)
			ambient_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MAPPEDPHONG::_SetKD(const _DOUBLE k)
	{
		if(diffuse_brdf)
			diffuse_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MAPPEDPHONG::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->_SETCD(c);
		if(diffuse_brdf)
			diffuse_brdf->_SetCD(c);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDPHONG::_SetCS(const _COLOR4F &c)
	{
		if(specular_brdf)
			specular_brdf->_SetCS(c);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDPHONG::_SetNormal(CORE::HARDWARE::TEXTUREINFO *nrm)
	{
		this->normal_map = nrm;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDPHONG::_SetSpecular(CORE::HARDWARE::TEXTUREINFO *spec)
	{
		specular_brdf->specular_map = spec;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDPHONG::_SetDiffuse(CORE::HARDWARE::TEXTUREINFO *dif)
	{
		diffuse_brdf->diffuse_map = dif;
	}
}