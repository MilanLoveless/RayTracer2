// Hammersley.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Hammersley.h"

namespace ThreeD
{
	_HAMMERSLEY::_HAMMERSLEY()
		:_SAMPLER()
	{}

	_HAMMERSLEY::_HAMMERSLEY(const int ns)
		:_SAMPLER(ns)
	{
		_GenerateSamples();
	}

	_HAMMERSLEY::_HAMMERSLEY(const int ns, const int m)
		:_SAMPLER(ns, m)
	{
		_GenerateSamples();
	}

	_HAMMERSLEY::_HAMMERSLEY(const _HAMMERSLEY &h)
		:_SAMPLER(h)
	{
		_GenerateSamples();
	}

	_HAMMERSLEY& _HAMMERSLEY::operator=(const _HAMMERSLEY &h)
	{
		if(this == &h)
			return (*this);
		
		_SAMPLER::operator=(h);

		return(*this);
	}

	_HAMMERSLEY* _HAMMERSLEY::_Clone()
	{
		return (new _HAMMERSLEY(*this));
	}

	_HAMMERSLEY::~_HAMMERSLEY() {}

	_DOUBLE _HAMMERSLEY::_Phi(int j)
	{
		_DOUBLE x = 0.0;
		_DOUBLE f = 0.5;

		while(j)
		{
			x += f*(_DOUBLE)(j%2);
			j /= 2;
			f *= 0.5;
		}
		return (x);
	}

	void _HAMMERSLEY::_GenerateSamples()
	{
		for(int p = 0; p < num_sets; p++)
		{
			for(int q = 0; q < num_samples; q++)
			{
				_POINT2D pv((_DOUBLE)p/(_DOUBLE) num_samples, _Phi(q));
				samples.push_back(pv);
			}
		}
	}
}