// Regular.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sampler.h"

namespace ThreeD
{
	class _REGULAR : public _SAMPLER
	{
	public:
		_REGULAR();
		_REGULAR(const int ns);
		_REGULAR(const _REGULAR &reg);
		_REGULAR& operator= (const _REGULAR &reg);
		virtual _REGULAR* _Clone();
		~_REGULAR();

		virtual void _GenerateSamples();
	};
}