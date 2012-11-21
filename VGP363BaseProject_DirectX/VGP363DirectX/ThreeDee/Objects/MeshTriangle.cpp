// MeshTriangle.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MeshTriangle.h"

namespace ThreeD
{
	_MESHTRIANGLE* _MESHTRIANGLE::_Clone()
	{
		return new _MESHTRIANGLE(*this);
	}

	bool _MESHTRIANGLE::_Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr)
	{
		return false;
	}

	bool _MESHTRIANGLE::_ShadowHit(const _RAY &ray, _DOUBLE &tmin)
	{
		return false;
	}

}