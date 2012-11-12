// PointLight.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Light.h"
#include "../../Components/Constants.h"
#include "../../World/World.h"

namespace ThreeD
{
	class _POINTLIGHT : public _LIGHT
	{
	public:
		_POINTLIGHT(const _VERTEX4F &pos, const _COLOR4F &c, const _DOUBLE l);
		~_POINTLIGHT();

		virtual _VERTEX4F _GetDirection(_SHADEREC &sr);
		virtual _COLOR4F _L(_SHADEREC &sr);
		virtual bool _InShadow(const _RAY &ray, const _SHADEREC &sr);

		_DOUBLE ls;
		_COLOR4F color;
		_VERTEX4F location;
	};
}