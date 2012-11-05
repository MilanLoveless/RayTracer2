// MultiJittered.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MultiJittered.h"

namespace ThreeD
{
	_MULTIJITTERED::_MULTIJITTERED()
		:_SAMPLER()
	{}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_MULTIJITTERED::_MULTIJITTERED(const int ns)
		:_SAMPLER(ns)
	{
		_GenerateSamples();
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_MULTIJITTERED::_MULTIJITTERED(const int ns, const int m)
		:_SAMPLER(ns, m)
	{
		_GenerateSamples();
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_MULTIJITTERED::_MULTIJITTERED(const _MULTIJITTERED &mjs)
		: _SAMPLER(mjs)
	{
		_GenerateSamples();
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_MULTIJITTERED& _MULTIJITTERED::operator= (const _MULTIJITTERED &mjs)
	{
		if(this == &mjs)
		{
			return (*this);
		}

		_SAMPLER::operator=(mjs);

		return (*this);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_MULTIJITTERED::~_MULTIJITTERED()
	{

	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MULTIJITTERED::_GenerateSamples()
	{
		int n = (int)sqrt((float)num_samples);
		float subcell_width = 1.0 / ((float) num_samples);

		_POINT2D fill_point;
		for (int j = 0; j < num_samples * num_sets; j++)
		{
			samples.push_back(fill_point);
		}
	
		for (int p = 0; p < num_sets; p++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					samples[i * n + j + p * num_samples].x = (i * n + j) * subcell_width + (_RandFloat * subcell_width);
					samples[i * n + j + p * num_samples].y = (j * n + i) * subcell_width + (_RandFloat * subcell_width);
				}
			}
		}

		for (int p = 0; p < num_sets; p++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					int k = (int)(_RandFloat * (n - j) + j); //Test This
					float t = samples[i * n + j + p * num_samples].x;
					samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
					samples[i * n + k + p * num_samples].x = t;
				}
			}
		}

		for (int p = 0; p < num_sets; p++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					int k = (int)(_RandFloat * (n - j) + j); // Test This
					float t = samples[j * n + i + p * num_samples].y;
					samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
					samples[k * n + i + p * num_samples].y = t;
				}
			}
		}
	}
}