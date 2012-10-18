// Color.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>

namespace ThreeD
{
	class _COLOR4F
	{
	public:
	
		double a, r, g, b;									
				
		_COLOR4F(void);
		~_COLOR4F(void);
		_COLOR4F(double c);
		_COLOR4F(double _a, double _r, double _g, double _b);
		_COLOR4F(const _COLOR4F &c);
				
		_COLOR4F& operator= (const _COLOR4F &cc);
		
		_COLOR4F operator+ (const _COLOR4F &c);
		_COLOR4F& operator+= (const _COLOR4F &c);
		
		_COLOR4F operator* (const double s);
		_COLOR4F& operator*= (const double s);
				
		_COLOR4F operator/ (const double s);
		_COLOR4F& operator/= (const double s);

		_COLOR4F operator* (const _COLOR4F &c);
		
		bool operator== (const _COLOR4F &c);

		_COLOR4F _Power(double p);
		
		double _Average();
		
		static _COLOR4F _AverageColor(const _COLOR4F &c1, const _COLOR4F &c2);
	};
}