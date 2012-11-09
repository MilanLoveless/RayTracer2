// Ambient.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Ambient.h"

namespace ThreeD
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	_AMBIENT::_AMBIENT()
		:_LIGHT()
	{
		ls = 1.0;
		color = _COLOR4F(0.1);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _AMBIENT::_GetDirection(_SHADEREC &sr)
	{
		return (_VERTEX4F(0.0, 0.0, 0.0, 0.0));
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_COLOR4F _AMBIENT::_L(_SHADEREC &sr)
	{
		return (color * ls);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}