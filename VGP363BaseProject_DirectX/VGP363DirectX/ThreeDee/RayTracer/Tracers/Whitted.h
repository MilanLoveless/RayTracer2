// Whitted.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Tracer.h"

namespace ThreeD
{
	class _WHITTED : public _TRACER
	{
	public:
		_WHITTED();
		_WHITTED(_WORLD *world);
		~_WHITTED();

		virtual _COLOR4F _TraceRay(const _RAY &ray, const int depth);
	};
}