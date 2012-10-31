// PointLight.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Light.h"

namespace ThreeD
{
	class _POINTLIGHT : public _LIGHT
	{
	public:
		virtual _VERTEX4F _GetDirection(_SHADEREC &sr);
		virtual _COLOR4F _L(_SHADEREC &sr);
		
		double ls;
		_COLOR4F color;
		_VERTEX4F location;
	};
}