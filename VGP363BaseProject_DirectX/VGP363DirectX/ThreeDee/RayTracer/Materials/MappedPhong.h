// MappedPhong.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Material.h"
#include "../BRDF/Lambertian.h"
#include "../BRDF/GlossySpecular.h"
#include "../../World/World.h"
#include "../../../CORE/CORE.Hardware.3D.Texture.h"
#include "../../../CORE/CORE.Drawing.h"
#include "../../../CORE/3D/CORE.Drawing.Primitives.h"
#include "../BRDF/Iridescent.h"

namespace ThreeD
{
	class _MAPPEDPHONG : public _MATERIAL
	{
	public:
		_MAPPEDPHONG();
		_MAPPEDPHONG(const _MAPPEDPHONG &mat);
		virtual _MATERIAL* _Clone();
		_MAPPEDPHONG& operator= (const _MAPPEDPHONG &mat);
		~_MAPPEDPHONG();

		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetKS(const _DOUBLE k);
		void _SetCD(const _COLOR4F &c);
		void _SetCS(const _COLOR4F &c);
		void _SetNormal(CORE::HARDWARE::TEXTUREINFO *nrm);
		void _SetSpecular(CORE::HARDWARE::TEXTUREINFO *spec);
		void _SetDiffuse(CORE::HARDWARE::TEXTUREINFO *nrm);
		virtual _COLOR4F _Shade(_SHADEREC &sr);

		_LAMBERTIAN *ambient_brdf;
		_IRIDESCENT *iridescent_brdf;
		_GLOSSYSPECULAR *specular_brdf;
		CORE::HARDWARE::TEXTUREINFO *normal_map;
	};
}
