// Material.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//#include "../Misc/ShadeRec.h"

namespace ThreeD
{
	class _SHADEREC;

	class _MATERIAL
	{
	public:
		virtual _COLOR4F _Shade(_SHADEREC &sr) = 0;
		virtual _COLOR4F _AreaLightShade(_SHADEREC &sr) = 0;
		virtual _COLOR4F _PathShade(_SHADEREC &sr) = 0;
	};
}