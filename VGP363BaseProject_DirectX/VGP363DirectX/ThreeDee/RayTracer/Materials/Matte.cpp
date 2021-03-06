// Matte.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Matte.h"


namespace ThreeD
{
	_MATTE::_MATTE()
		:_MATERIAL(),
		ambient_brdf(new _LAMBERTIAN()),
		diffuse_brdf(new _LAMBERTIAN())
	{
		ambient_brdf->_SETCD(_COLOR4F(1.0, 0.9, 0.1, 0.3));
		ambient_brdf->_SetKA(1.0);
		diffuse_brdf->_SETCD(_COLOR4F(1.0, 0.9, 0.1, 0.3));
		diffuse_brdf->_SetKD(1.0);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATTE::_MATTE(const _MATTE &mat)
		: _MATERIAL(mat)
	{
		if(mat.ambient_brdf)
			ambient_brdf = mat.ambient_brdf->_Clone();
		else ambient_brdf = NULL;

		if(mat.diffuse_brdf)
			diffuse_brdf = mat.diffuse_brdf->_Clone();
		else diffuse_brdf = NULL;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATERIAL* _MATTE::_Clone()
	{
		return (new _MATTE(*this));
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATTE& _MATTE::operator= (const _MATTE &mat)
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

		return (*this);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_MATTE::~_MATTE()
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
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _MATTE::_Shade(_SHADEREC &sr)
	{
		_VERTEX4F wo = sr.ray.vector * -1.0;
		_COLOR4F L = ambient_brdf->_Rho(sr, wo) * sr.world_ptr->ambient_ptr->_L(sr);
		int num_lights = sr.world_ptr->lights.size();

		for (int j = 0; j < num_lights; j++)
		{
			_VERTEX4F wi = sr.world_ptr->lights[j]->_GetDirection(sr);
			float ndotwi = wi._DotProduct(sr.normal, wi);
			
			if(ndotwi > 0.0)
				L+= diffuse_brdf->_F(sr, wo, wi) * sr.world_ptr->lights[j]->_L(sr) * ndotwi;
		}
		return L;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MATTE::_SetKA(const _DOUBLE k)
	{
		if(ambient_brdf)
			ambient_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MATTE::_SetKD(const _DOUBLE k)
	{
		if(diffuse_brdf)
			diffuse_brdf->kd = k;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////	
	void _MATTE::_SetCD(const _COLOR4F &c)
	{
		if(ambient_brdf)
			ambient_brdf->cd = c;
		if(diffuse_brdf)
			diffuse_brdf->cd = c;
	}
}