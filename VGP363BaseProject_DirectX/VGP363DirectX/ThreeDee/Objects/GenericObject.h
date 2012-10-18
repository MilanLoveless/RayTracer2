// GenericObject.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Components/Primitives.h"


namespace ThreeD
{
	class _GENERICOBJECT
	{
	public:


		_GENERICOBJECT();
		virtual ~_GENERICOBJECT();
		_GENERICOBJECT(const _GENERICOBJECT &object);
		
		virtual bool _Hit(const _RAY &ray, double &t);

	};
}