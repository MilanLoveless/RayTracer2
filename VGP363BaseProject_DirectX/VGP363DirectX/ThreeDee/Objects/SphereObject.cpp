// SphereObject.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SphereObject.h"
#include <math.h>

namespace ThreeD
{

	void _SPHERE::_SetCenter(const _VERTEX4F& c)
	{
		center = c;
	}
		
	void _SPHERE::_SetCenter(const double x, const double y, const double z)
	{
		center.x = x;
		center.y = y;
		center.z = z;
	}
		
	void _SPHERE::_SetRadius(const double r)
	{
		radius = r;
	}

	// This file contains the definition of the class sphere

	const double _SPHERE::kEpsilon = 0.001;
					
	// ---------------------------------------------------------------- default constructor

	_SPHERE::_SPHERE(void)
		: _GENERICOBJECT()
	
	{
		center = _VERTEX4F(0.0, 0.0, 0.0, 1.0);
		radius = 1.0;
	}


	// ---------------------------------------------------------------- constructor

	_SPHERE::_SPHERE(_VERTEX4F c, double r)
		: 	_GENERICOBJECT(),
			center(c),
			radius(r)
	{}

	_SPHERE::_SPHERE(_VERTEX4F c1, double r, _COLOR4F c2)
		: 	_GENERICOBJECT(),
			center(c1),
			radius(r)
	{
		_GENERICOBJECT::_SetColor(c2);
	}


	// ---------------------------------------------------------------- clone

	_SPHERE* _SPHERE::_Clone(void) const
	{
		return (new _SPHERE(*this));
	}


	// ---------------------------------------------------------------- copy constructor

	_SPHERE::_SPHERE (const _SPHERE& sphere)
		: 	_GENERICOBJECT(sphere),
			center(sphere.center),
			radius(sphere.radius)
	{}



	// ---------------------------------------------------------------- assignment operator

	_SPHERE& 
	_SPHERE::operator= (const _SPHERE& rhs)		
	{
		if (this == &rhs)
			return (*this);

		_GENERICOBJECT::operator= (rhs);

		center 	= rhs.center;
		radius	= rhs.radius;

		return (*this);
	}


	// ---------------------------------------------------------------- destructor

	_SPHERE::~_SPHERE(void) {}


	//---------------------------------------------------------------- hit

	bool
	_SPHERE::_Hit(const _RAY& ray, double& tmin, _HITINFO& sr) {
		double 		t;
		_VERTEX4F	temp 	= _VERTEX4F(ray.origin) - center;
		double 		a 		= _VERTEX4F::_DotProduct(ray.vector, ray.vector); // if we normalize the vector before doing this calculation, a = 1.0 and cleanly factors out of this equation
		double 		b 		= _VERTEX4F::_DotProduct(temp, ray.vector) * 2.0;
		double 		c 		= _VERTEX4F::_DotProduct(temp, temp) - radius * radius;
		double 		disc	= b * b - 4.0 * a * c;
	
		if (disc < 0.0)
			return(false);
		else
		{	
			double e = sqrt(disc);
			double denom = 2.0 * a;
			t = (-b - e) / denom;    // smaller root
	
			if (t > kEpsilon) {
				tmin = t;
				sr.normal.vector = (temp + _VERTEX4F(ray.vector)*t) / radius;
				sr.normal.origin = _VERTEX4F(ray.origin) + (_VERTEX4F(ray.vector) * t);
				sr.distance = temp._Magnitude();
				sr.hitcolor = this->color;
				return (true);
			} 
	
			t = (-b + e) / denom;    // larger root
	
			if (t > kEpsilon) {
				tmin = t;
				sr.normal.vector = (temp + _VERTEX4F(ray.vector)*t) / radius;
				sr.normal.origin = _VERTEX4F(ray.origin) + (_VERTEX4F(ray.vector) * t);
				sr.distance = temp._Magnitude();
				sr.hitcolor = this->color;
				return (true);
			} 
		}
	
		return (false);
	}

}