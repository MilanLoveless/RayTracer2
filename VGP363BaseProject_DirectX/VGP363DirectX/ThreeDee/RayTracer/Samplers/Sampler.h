// Sampler.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Components/Point2D.h"
#include <vector>

using namespace std;

namespace ThreeD
{
	class _SAMPLER
	{
	public:
		virtual void _GenerateSamples() = 0;
		void _SetupShuffledIndicies();
		void _ShuffleSamples();
		_POINT2D _SampleUnitSquare();

		int numsamples;
		int numsets;
		vector<_POINT2D> samples;
		vector<int> shuffledindicies;
		unsigned long count;
		int jump;
	};
}