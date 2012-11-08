// Matte.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "Material.h"
#include "../BRDF/Lambertian.h"

namespace ThreeD
{
	class _MATTE : public _MATERIAL
	{
	public:
		_MATTE();
		_MATTE(const _MATTE &mat);
		virtual _MATERIAL* _Clone();
		_MATTE& operator= (const _MATTE &mat);
		~_MATTE();

		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetCD(const _COLOR4F &c);

		virtual _COLOR4F _Shade(_SHADEREC &sr);

		_LAMBERTIAN *ambient_brdf;
		_LAMBERTIAN *diffuse_brdf;
	};
}
