// NRooks.h
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Sampler.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _NROOKS : public _SAMPLER
	{
	public:
		_NROOKS();
		_NROOKS(const int num_samples);
		_NROOKS(const int num_samples, const int m);
		_NROOKS(const _NROOKS &nr);

		_NROOKS& operator = (const _NROOKS &rhs);

		virtual _NROOKS* _Clone();
		~_NROOKS();

		virtual void _GenerateSamples();
	};
}