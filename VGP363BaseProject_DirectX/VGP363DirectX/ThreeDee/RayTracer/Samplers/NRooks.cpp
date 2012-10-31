// NROOKS.cpp
////////////////////////////////////////////////////////////////////////////

#include "NRooks.h"

namespace ThreeD
{
	_NROOKS::_NROOKS()
		: _SAMPLER()
	{

	}

	_NROOKS::_NROOKS(const int numsamples)
		: _SAMPLER(numsamples)
	{
		_GenerateSamples();
	}

	_NROOKS::_NROOKS(const int numsamples, const int m)
		: _SAMPLER(numsamples, m)
	{
		_GenerateSamples();
	}
}