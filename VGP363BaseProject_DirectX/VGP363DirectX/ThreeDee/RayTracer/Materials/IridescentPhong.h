// IridescentPhong.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/Iridescent.h"
#include "../BRDF/GlossySpecular.h"
#include "../../World/World.h"

namespace ThreeD
{
	class _IRIDESCENTPHONG : public _MATERIAL
	{
	public:
		_IRIDESCENTPHONG();
		_IRIDESCENTPHONG(const _IRIDESCENTPHONG &mat);
		virtual _MATERIAL* _Clone();
		_IRIDESCENTPHONG& operator= (const _IRIDESCENTPHONG &mat);
		~_IRIDESCENTPHONG();

		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetKS(const _DOUBLE k);
		void _SetCD(const _COLOR4F &c);
		void _SetCS(const _COLOR4F &c);

		virtual _COLOR4F _Shade(_SHADEREC &sr);

		_LAMBERTIAN *ambient_brdf;
		_IRIDESCENT *iridescent_brdf;
		_GLOSSYSPECULAR *specular_brdf;
	};
}
