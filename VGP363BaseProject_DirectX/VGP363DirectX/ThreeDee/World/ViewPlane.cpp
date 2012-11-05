// ViewPlane.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ViewPlane.h"
#include "../RayTracer/Samplers/MultiJittered.h"
#include "../RayTracer/Samplers/Regular.h"

namespace ThreeD
{
	void _VIEWPLANE::_SetSamples(const int n)
	{
		num_samples = n;

		if(sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
		
		if(num_samples > 1)
		{
			sampler_ptr = new _MULTIJITTERED(num_samples);
		}
		else
		{
			sampler_ptr = new _REGULAR(1);
		}
	}
}