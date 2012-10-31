// Sampler.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sampler.h"

namespace ThreeD
{
	_POINT2D _SAMPLER::_SampleUnitSquare()
	{
		if(count % numsamples == 0)
		{
			jump = (rand_int() % numsets) * numsamples;
		}
		return (samples[count++ % (numsamples * numsets)]);
	}
}