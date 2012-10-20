//HitInfo.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Ray.h"
#include "../../Components/Color.h"
#include "../../Components/Vertex.h"
#include "../../Objects/GenericObject.h"

namespace ThreeD
{
	struct _HITINFO
	{
	public:
		_RAY normal;
		double distance;
		_COLOR4F hitcolor;
	};
}