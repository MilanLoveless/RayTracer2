// PointLight.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Light.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _POINTLIGHT : public _LIGHT
	{
	public:
		virtual _VERTEX4F _GetDirection(_SHADEREC &sr);
		virtual _COLOR4F _L(_SHADEREC &sr);
		
		_DOUBLE ls;
		_COLOR4F color;
		_VERTEX4F location;
	};
}