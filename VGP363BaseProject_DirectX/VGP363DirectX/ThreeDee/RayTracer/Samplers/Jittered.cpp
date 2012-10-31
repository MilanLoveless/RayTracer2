// Jittered.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Jittered.h"

namespace ThreeD
{
	void _JITTERED::_GenerateSamples()
	{
		int n = (int) sqrt((float)numsamples);

		for (int p = 0; p < numsets; p++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					_POINT2D sp((k + rand_float()) / n, (j + rand_float()) / n);
					samples.push_back(sp);
				}
			}
		}
	}
}