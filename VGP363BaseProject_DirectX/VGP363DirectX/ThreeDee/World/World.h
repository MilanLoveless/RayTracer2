#pragma once

#include <vector>

#include "../Cameras/RayCamera.h"

#include "../Components/Color.h"

#include "../RayTracer/Misc/Ray.h"
#include "../RayTracer/Tracers/RayTracer.h"

#include "../Objects/GenericObject.h"
#include "../Objects/SphereObject.h"
#include "../Lights/Light.h"

using namespace std;

namespace ThreeD
{
	class _WORLD
	{
	public:
		int maxdepth;
		float *zb;
		_COLOR4F backgroundcolor;
		_TRACER *tracer_ptr;
		RayCamera *camera_ptr;
		vector<_GENERICOBJECT*> objects;
		vector<_LIGHT*> lights;
		
		_WORLD();
		~_WORLD();
		
		void _AddObject(_GENERICOBJECT *object_ptr);
		void _Build();

	};
}