#include "GenericObject.h"

namespace ThreeD
{

	void _GENERICOBJECT::_SetColor(const _COLOR4F &c)
	{
		color = c;
	}

	void _GENERICOBJECT::_SetColor(const float a, const float r, const float g, const float b) {
		color.a = a;
		color.r = r;
		color.b = b;
		color.g = g;
	}

	_COLOR4F _GENERICOBJECT::_GetColor()
	{
		return (color);
	}

	_GENERICOBJECT::_GENERICOBJECT()
	{
		color = _COLOR4F(0.25);
	}

	_GENERICOBJECT::_GENERICOBJECT (const _GENERICOBJECT &obj)
	{
		color = obj.color;
	}

	_GENERICOBJECT&	_GENERICOBJECT::operator= (const _GENERICOBJECT& obj)
	{
	
		if (this == &obj)
			return (*this);
		
		color = obj.color;

		return (*this);
	}

	_GENERICOBJECT::~_GENERICOBJECT ()
	{
	
	}

}