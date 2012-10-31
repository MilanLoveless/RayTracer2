// ViewPlane.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ViewPlane.h"

namespace ThreeD
{
	void _VIEWPLANE::_SetSampler(_SAMPLER *sp)
	{
		if (sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}
		numsamples = sp->_GetNumSamples();
		sampler_ptr = sp;
	}
	
	void _VIEWPLANE::_SetSamples(const int n)
	{
		numsamples = n;

		if(sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}

		if (numsamples > 1)
		{
			sampler_ptr = new _MULTIJITTERED(numsamples);
		}
		else
		{
			sampler_ptr = new _REGULAR(1);
		}
	}

}