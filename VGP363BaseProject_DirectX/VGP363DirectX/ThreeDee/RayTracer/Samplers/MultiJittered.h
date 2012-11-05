// MultiJittered.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Sampler.h"

namespace ThreeD
{
	class _MULTIJITTERED : public _SAMPLER
	{
	public:
		_MULTIJITTERED();
		_MULTIJITTERED(const int ns);
		_MULTIJITTERED(const int ns, const int m);
		_MULTIJITTERED(const _MULTIJITTERED &mjs);
		_MULTIJITTERED& operator= (const _MULTIJITTERED &mjs);
		~_MULTIJITTERED();

		virtual void _GenerateSamples();
	};
}