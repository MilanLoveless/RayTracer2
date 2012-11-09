// Light.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Color.h"
#include "../Misc/ShadeRec.h"

namespace ThreeD
{
	class _LIGHT
	{
	public:
		_LIGHT();
		~_LIGHT();
		virtual _VERTEX4F _GetDirection(_SHADEREC &sr) = 0;
		virtual _COLOR4F _L(_SHADEREC &sr) = 0;

		bool shadows;
	};
}