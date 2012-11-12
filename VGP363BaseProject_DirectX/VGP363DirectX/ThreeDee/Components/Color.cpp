// Color.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Color.h"

namespace ThreeD
{

	_COLOR4F::_COLOR4F()
	{
		a = 1.0;
		r = 0.5;
		g = 0.5;
		b = 0.5;
	}

	_COLOR4F::_COLOR4F(_DOUBLE c)						
	{
		a = 1.0;
		r = c;
		g = c;
		b = c;
	}

	_COLOR4F::_COLOR4F(_DOUBLE _a, _DOUBLE _r, _DOUBLE _g, _DOUBLE _b)	
	{
		a = _a;
		r = _r;
		g = _g;
		b = _b;
	}

	_COLOR4F::_COLOR4F(const _COLOR4F &c)
	{
		a = c.a;
		r = c.r;
		g = c.g;
		b = c.b;
	}

	_COLOR4F::~_COLOR4F()		
	{
	
	}
	_COLOR4F& _COLOR4F::operator= (const _COLOR4F &cc)
	{
		if (this == &cc)
			return (*this);
		
		a = cc.a;
		r = cc.r;
		g = cc.g;
		b = cc.b;
		
		return (*this);
	}
 
	_COLOR4F _COLOR4F::_Power(_DOUBLE p)
	{
		return _COLOR4F(this->a, pow(this->r, p), pow(this->g, p), pow(this->b, p));
	}

	_COLOR4F _COLOR4F::operator+ (const _COLOR4F &c)
	{
		return (_COLOR4F(a, r + c.r, g + c.g, b + c.b));
	}

	_COLOR4F& _COLOR4F::operator+= (const _COLOR4F &c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return (*this);
	}

	_COLOR4F _COLOR4F::operator* (const _DOUBLE s)
	{
		return (_COLOR4F (a, r * s, g * s, b * s));	
	}

	_COLOR4F& _COLOR4F::operator*= (const _DOUBLE s)
	{
		r *= a;
		g *= a;
		b *= a;
		return (*this);
	}

	_COLOR4F _COLOR4F::operator/ (const _DOUBLE s)
	{
		return (_COLOR4F (a, r / s, g / s, b / s));
	}

	_COLOR4F& _COLOR4F::operator/= (const _DOUBLE s)
	{	
		r /= s;
		g /= s;
		b /= s;
		return (*this);
	}

	_COLOR4F _COLOR4F::operator* (const _COLOR4F& c)
	{
		return (_COLOR4F (a, r * c.r, g * c.g, b * c.b));
	} 

	bool _COLOR4F::operator== (const _COLOR4F& c)
	{
		return (a == c.a && r == c.r && g == c.g && b == c.b);
	}

	_DOUBLE _COLOR4F::_Average()
	{
		return (0.333333333333 * (r + g + b));
	}

	_COLOR4F _COLOR4F::_AverageColor(const _COLOR4F &c1, const _COLOR4F &c2)
	{
		return _COLOR4F((c1.a+c2.a)/2.0, (c1.r+c2.r)/2.0, (c1.g+c2.g)/2.0, (c1.b+c2.b)/2.0);
	}

	void _COLOR4F::_Normalize()
	{
		float max = 1.0;
		if(r > 1.0) max = r;
		if(g > 1.0 && g > r) max = g;
		if(b > 1.0 && b > g && b > r) max = b;
		r /= max;
		g /= max;
		b /= max;
		//if(r > 1.0) r = 1.0;
		//if(r < 0.0) r = 0.0;
		//if(g > 1.0) g = 1.0;
		//if(g < 0.0) g = 0.0;
		//if(b > 1.0) b = 1.0;
		//if(b < 0.0) b = 0.0;
	}
}