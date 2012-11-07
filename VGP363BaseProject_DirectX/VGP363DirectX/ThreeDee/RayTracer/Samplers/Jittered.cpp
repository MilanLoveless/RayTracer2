// Jittered.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Jittered.h"

namespace ThreeD
{
	void _JITTERED::_GenerateSamples()
	{
		int n = (int) sqrt((float)num_samples);

		for (int p = 0; p < num_sets; p++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					_POINT2D sp((k + _RandFloat) / n, (j + _RandFloat) / n);
					samples.push_back(sp);
				}
			}
		}
	}
}