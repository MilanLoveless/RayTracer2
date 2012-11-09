// Color.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include "Constants.h"

namespace ThreeD
{
	class _COLOR4F
	{
	public:
	
		_DOUBLE a, r, g, b;									
				
		_COLOR4F(void);
		~_COLOR4F(void);
		_COLOR4F(_DOUBLE c);
		_COLOR4F(_DOUBLE _a, _DOUBLE _r, _DOUBLE _g, _DOUBLE _b);
		_COLOR4F(const _COLOR4F &c);
				
		_COLOR4F& operator= (const _COLOR4F &cc);
		
		_COLOR4F operator+ (const _COLOR4F &c);
		_COLOR4F& operator+= (const _COLOR4F &c);
		
		_COLOR4F operator* (const _DOUBLE s);
		_COLOR4F& operator*= (const _DOUBLE s);
				
		_COLOR4F operator/ (const _DOUBLE s);
		_COLOR4F& operator/= (const _DOUBLE s);

		_COLOR4F operator* (const _COLOR4F &c);
		
		bool operator== (const _COLOR4F &c);

		_COLOR4F _Power(_DOUBLE p);
		
		_DOUBLE _Average();
		
		static _COLOR4F _AverageColor(const _COLOR4F &c1, const _COLOR4F &c2);

		void _Normalize();
	};
}