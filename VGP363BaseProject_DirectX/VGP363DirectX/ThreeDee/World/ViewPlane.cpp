// ViewPlane.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ViewPlane.h"

namespace ThreeD
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VIEWPLANE::_VIEWPLANE() {}
	
	_VIEWPLANE::_VIEWPLANE(const _VIEWPLANE &vp) {}
	
	_VIEWPLANE& _VIEWPLANE::operator= (const _VIEWPLANE &vp)
	{
		if(this == &vp)
			return (*this);

		return (*this);
	}
	
	_VIEWPLANE::~_VIEWPLANE() {}
	
	void _VIEWPLANE::_SetHRes(const int h)
	{
		hres = h;
	}

	void _VIEWPLANE::_SetVRes(const int v)
	{
		vres = v;
	}

	void _VIEWPLANE::_SetPixelSize(const _DOUBLE size)
	{
		s = size;
	}

	void _VIEWPLANE::_SetGamma(const _DOUBLE g)
	{
		gamma = g;
		inv_gamma = 1.0 / g;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _VIEWPLANE::_SetSampler(_SAMPLER *sp)
	{
		if (sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
		num_samples = sp->_GetNumSamples();
		sampler_ptr = sp;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _VIEWPLANE::_SetSamples(const int n)
	{
		num_samples = n;

		if(sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}

		if (num_samples > 1)
		{
			sampler_ptr = new _MULTIJITTERED(num_samples);
		}
		else
		{
			sampler_ptr = new _REGULAR(1);
		}
	}

}