// Hammersley.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Sampler.h"
#include "../../Components/Constants.h"

namespace ThreeD
{
	class _HAMMERSLEY : public _SAMPLER
	{
	public:
		_HAMMERSLEY();
		_HAMMERSLEY(const int ns);
		_HAMMERSLEY(const int ns, const int m);
		_HAMMERSLEY(const _HAMMERSLEY &h);
		_HAMMERSLEY& operator= (const _HAMMERSLEY &h);
		virtual _HAMMERSLEY* _Clone();
		~_HAMMERSLEY();
		
		_DOUBLE _Phi(int j);
		virtual void _GenerateSamples();
		
	};
}