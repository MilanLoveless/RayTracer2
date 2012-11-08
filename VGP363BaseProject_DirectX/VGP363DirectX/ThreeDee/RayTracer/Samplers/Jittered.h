// Jittered.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include "Sampler.h"

namespace ThreeD
{
	class _JITTERED : public _SAMPLER
	{
	public:
		_JITTERED();
		_JITTERED(const int ns);
		_JITTERED(const int ns, const int m);
		_JITTERED(const _JITTERED &j);
		_JITTERED& operator= (const _JITTERED &j);
		~_JITTERED();
		virtual _JITTERED* _Clone();

		virtual void _GenerateSamples();
	};

}