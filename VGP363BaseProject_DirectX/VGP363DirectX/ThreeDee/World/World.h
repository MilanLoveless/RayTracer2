#pragma once

#include <vector>

#include "../Components/Color.h"
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
		vector<_GENERICOBJECT*> objects;
		vector<_LIGHT*> lights;
		
		_WORLD();
		~_WORLD();
		
		void _AddObject(_GENERICOBJECT *object_ptr);
		void _AddLight(_LIGHT *light_ptr);
		void _Build();

	protected:
		void _DeleteObjects();
		void _DeleteLights();
	};
}