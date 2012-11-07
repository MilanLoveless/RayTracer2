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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	_WORLD::~_WORLD()
	{
		_DeleteObjects();
		_DeleteLights();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//void _WORLD::_AddObject(_GENERICOBJECT *object_ptr) {
	//	if(object_ptr == NULL) return;
	//	this->objects.push_back(object_ptr);
	//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	_SHADEREC _WORLD::_HitObjects(const _RAY &ray)
//	{
//		_SHADEREC sr(*this);
//		double t;
//		_VERTEX4F normal;
//		_VERTEX4F local_hit_point;
//		double tmin = kHugeValue;
//		int num_objects = objects.size();
//
//		for(int j = 0; j < num_objects; j++)
//		{
//			if (objects[j]->_Hit(ray, t, sr) && (t < tmin))
//			{
//				sr.hit_an_object = true;
//				tmin = t;
//				sr.material_ptr = objects[j]->_GetMaterial();
//				sr.hit_point = _VERTEX4F(ray.origin) + _VERTEX4F(ray.vector) * t;
//				normal = sr.normal;
//				local_hit_point = sr.local_hit_point;
//			}
//		}
//		
//		if(sr.hit_an_object)
//		{
//			sr.t = tmin;
//			sr.normal = normal;
//			sr.local_hit_point = local_hit_point;
//		}
//		
//		return sr;
//	}
}

