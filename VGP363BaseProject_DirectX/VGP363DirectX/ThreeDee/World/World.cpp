// World.cpp
///////////////////////////////////////////////////
#include "World.h"

namespace ThreeD
{
	_WORLD::_WORLD()
	{
		backgroundcolor = _COLOR4F(0.0);
		maxdepth = 3;
	}
	
	_WORLD::~_WORLD()
	{
		_DeleteObjects();
		_DeleteLights();
	}

	void _WORLD::_AddObject(_GENERICOBJECT *object_ptr) {
		if(object_ptr == NULL) return;
		this->objects.push_back(object_ptr);
	}

	void _WORLD::_DeleteObjects()
	{
		int nobjects = objects.size();

		for(int j = 0; j < nobjects; j++)
		{
			delete objects[j];
			objects[j] = NULL;
		}

		objects.erase(objects.begin(), objects.end());
	}

	void _WORLD::_DeleteLights()
	{
		int nlights = lights.size();

		for(int j = 0; j < nlights; j++)
		{
			delete lights[j];
			lights[j] = NULL;
		}

		lights.erase(lights.begin(), lights.end());
	}

}

