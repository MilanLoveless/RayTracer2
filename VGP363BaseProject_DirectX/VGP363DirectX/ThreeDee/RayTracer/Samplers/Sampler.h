// Sampler.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Misc/Point2D.h"
#include "../../Components/Vertex.h"
#include <vector>
#include <algorithm>
#include "../../Components/Constants.h"


using namespace std;

namespace ThreeD
{
	class _SAMPLER
	{
	public:
		_SAMPLER();
		_SAMPLER(const int num);
		_SAMPLER(const int ns, const int n_sets);
		_SAMPLER(const _SAMPLER & s);
		_SAMPLER& operator = (const _SAMPLER &s);
		//virtual _SAMPLER* _Clone() = 0;
		~_SAMPLER();
		
		void _SetNumSets(const int ns);
		void _SetNumSamples(const int ns);
		int _GetNumSamples();
		void _ShuffleXCoords();
		void _ShuffleYCoords();
		void _SetupShuffledIndices();
		void _MapToDisk();
		void _MapToHemisphere(const _DOUBLE exp);
		void _MapToSphere();
		virtual void _GenerateSamples() = 0;
		void _ShuffleSamples();
		
		_POINT2D _SampleSquare();
		_POINT2D _SampleDisk();
		_VERTEX4F _SampleHemisphere();
		_VERTEX4F _SampleSphere();

		int num_samples;
		int num_sets;
		vector<_POINT2D> samples;
		vector<int> shuffled_indices;
		vector<_POINT2D> disk_samples;
		vector<_VERTEX4F> hemisphere_samples;
		vector<_VERTEX4F> sphere_samples;
		unsigned long count;
		int jump;
	};
}

