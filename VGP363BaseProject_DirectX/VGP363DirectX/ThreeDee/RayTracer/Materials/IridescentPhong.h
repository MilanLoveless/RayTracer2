// IridescentPhong.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/GlossySpecular.h"
#include "../../World/World.h"

namespace ThreeD
{
	class _IRIDESCENT : public _MATERIAL
	{
	public:
		_IRIDESCENT();
		_IRIDESCENT(const _IRIDESCENT &mat);
		virtual _MATERIAL* _Clone();
		_IRIDESCENT& operator= (const _IRIDESCENT &mat);
		~_IRIDESCENT();

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
