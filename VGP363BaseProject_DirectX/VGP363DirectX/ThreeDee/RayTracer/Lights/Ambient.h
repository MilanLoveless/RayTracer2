// Ambient.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Light.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _AMBIENT : public _LIGHT
	{
	public:
		_AMBIENT();

		
		virtual _VERTEX4F _GetDirection(_SHADEREC &sr);
		virtual _COLOR4F _L(_SHADEREC &sr);
		
		_DOUBLE ls;
		_COLOR4F color;
	};
}