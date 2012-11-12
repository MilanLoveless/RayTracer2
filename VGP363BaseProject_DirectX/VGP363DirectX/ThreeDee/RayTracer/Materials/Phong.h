// Phong.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/GlossySpecular.h"
#include "../../World/World.h"

namespace ThreeD
{
	class _PHONG : public _MATERIAL
	{
	public:
		_PHONG();
		_PHONG(const _PHONG &mat);
		virtual _MATERIAL* _Clone();
		_PHONG& operator= (const _PHONG &mat);
		~_PHONG();

		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetKS(const _DOUBLE k);
		void _SetCD(const _COLOR4F &c);
		void _SetCS(const _COLOR4F &c);

		virtual _COLOR4F _Shade(_SHADEREC &sr);

		_LAMBERTIAN *ambient_brdf;
		_LAMBERTIAN *diffuse_brdf;
		_GLOSSYSPECULAR *specular_brdf;
	};
}
