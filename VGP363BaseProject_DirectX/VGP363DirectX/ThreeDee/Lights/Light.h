// Light.h
////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Components/Vertex.h"
#include "../Components/Color.h"

namespace ThreeD
{
	class _LIGHT
	{
	public:
		_VERTEX4F position; //The position of the light in worldspace
		_VERTEX4F direction; //The direction that the light is facing in worldspace
		double intensity; //The intensity of the light
		_COLOR4F color; //The color that the light emits
	};
}