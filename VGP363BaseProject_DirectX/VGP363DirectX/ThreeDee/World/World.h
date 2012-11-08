// World.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

#include "../Components/Color.h"
#include "../RayTracer/Misc/ShadeRec.h"
#include "../Objects/GeometricObject.h"
#include "../Objects/SphereObject.h"
#include "../RayTracer/Lights/Light.h"
#include "../Components/Constants.h"
#include "ViewPlane.h"

using namespace std;

namespace ThreeD
{
	class _WORLD
	{
	public:
		int maxdepth;
		_VIEWPLANE vp;
		_COLOR4F backgroundcolor;
		vector<_GEOMETRICOBJECT*> objects;
		vector<_LIGHT*> lights;
		
		_WORLD();
		~_WORLD();
		
		void _AddObject(_GEOMETRICOBJECT *object_ptr);
		void _AddLight(_LIGHT *light_ptr);
		void _Build();
		_SHADEREC _HitObjects(const _RAY &ray);

	protected:
		void _DeleteObjects();
		void _DeleteLights();
	};
}