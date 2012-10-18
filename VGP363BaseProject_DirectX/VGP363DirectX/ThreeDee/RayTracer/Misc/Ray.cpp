#include "Ray.h"

namespace ThreeD
{
	_RAY::_RAY()
	{
		this->origin = _VERTEX4F(0.0, 0.0, 0.0, 1.0);
		this->vector = _VERTEX4F(0.0, 0.0, 1.0, 0.0);
	}

	_RAY::_RAY(const _VERTEX4F &point, const _VERTEX4F &dir)
	{
		this->origin = point;
		this->vector = dir;
	}

	_RAY::_RAY(const _RAY &r)
	{
		this->origin = r.origin;
		this->vector = r.vector;
	}

	_RAY& _RAY::operator=(const _RAY &r)
	{
		origin = r.origin;
		vector = r.vector;
		return (*this);
	}

	_RAY::~_RAY()
	{

	}

}