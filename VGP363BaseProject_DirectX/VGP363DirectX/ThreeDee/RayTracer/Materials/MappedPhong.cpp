// MappedPhong.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MappedPhong.h"

namespace ThreeD
{
	_MAPPEDPHONG::_MAPPEDPHONG()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		iridescent_brdf(new _IRIDESCENT()),
		specular_brdf(new _GLOSSYSPECULAR()),
		normal_map(NULL)
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.1, 0.9, 0.9));
		ambient_brdf->_SetKA(1.0);
		iridescent_brdf->_SetCD(_COLOR4F(1.0, 0.1, 0.9, 0.9));
		iridescent_brdf->_SetKD(2.0);
		iridescent_brdf->_SetPower(0.5);
		iridescent_brdf->_SetRot(1.0);
		specular_brdf->_SetCS(_COLOR4F(1.0, 1.0, 1.0, 1.0));
		specular_brdf->_SetKS(1.0);
		specular_brdf->_SetPower(3.0);
		specular_brdf->_SetSampler(new _MULTIJITTERED(16), 3.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MAPPEDPHONG::_MAPPEDPHONG(const _MAPPEDPHONG &mat)
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
	_MAPPEDPHONG::~_MAPPEDPHONG()
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
	_COLOR4F _MAPPEDPHONG::_Shade(_SHADEREC &sr)
	{
		_VERTEX4F wo = sr.ray.vector * -1.0;
		_COLOR4F L = ambient_brdf->_Rho(sr, wo) * sr.world_ptr->ambient_ptr->_L(sr);
		
		CORE::HARDWARE::_LockTexture(normal_map);
		if(normal_map->_video != NULL)
			{
				int n = GetPixel(normal_map->_video, normal_map->_nActualWidth, normal_map->_nHeight, (int)(fmod(sr.hit_UV.x, 1) * normal_map->_nWidth), (int)(fmod(sr.hit_UV.y, 1) * normal_map->_nHeight));
				_VERTEX4F up1(0.01, 0.98, 0.03, 0.0);
				up1._Normalize();
				_VERTEX4F tangent = tangent._CrossProduct(sr.normal, up1);
				_VERTEX4F binormal = binormal._CrossProduct(tangent, sr.normal);
				tangent = tangent._CrossProduct(sr.normal, binormal);
				sr.normal = sr.normal * (_COLOR32_ARGB_GET_BLUE(n)/255.0) + binormal * (_COLOR32_ARGB_GET_GREEN(n)/255.0) + tangent * (_COLOR32_ARGB_GET_RED(n)/255.0);
				sr.normal._Normalize();
			}
		CORE::HARDWARE::_UnlockTexture(normal_map);

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
				L+= (iridescent_brdf->_F(sr, wo, wi)  + specular_brdf->_F(sr, wo, wi)) * sr.world_ptr->lights[j]->_L(sr) * ndotwi;
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
		if(iridescent_brdf)
			iridescent_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MAPPEDPHONG::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->_SETCD(c);
		if(iridescent_brdf)
			iridescent_brdf->_SetCD(c);
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

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MAPPEDPHONG::_SetDiffuse(CORE::HARDWARE::TEXTUREINFO *nrm)
	{

	}
}