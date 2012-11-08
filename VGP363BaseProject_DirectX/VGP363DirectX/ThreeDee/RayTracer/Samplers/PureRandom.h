// PureRandom.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sampler.h"

namespace ThreeD
{
	class _PURERANDOM : public _SAMPLER
	{
	public:
		_PURERANDOM();
		_PURERANDOM(const int ns);
		_PURERANDOM(const int ns, const int m);
		_PURERANDOM(const _PURERANDOM &r);
		_PURERANDOM& operator= (const _PURERANDOM &r);
		virtual _PURERANDOM* _Clone();
		~_PURERANDOM();

		virtual void _GenerateSamples();
	};
}