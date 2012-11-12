// SphereObject.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SphereObject.h"

namespace ThreeD
{
	const _DOUBLE _SPHERE::kEpsilon = 0.001;
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_SPHERE::_SPHERE()
		:_GEOMETRICOBJECT(),
		center(),
		radius(1.0)
	{
		material_ptr = new _PHONG();
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_SPHERE::_SPHERE(_VERTEX4F c, _DOUBLE r)
		:_GEOMETRICOBJECT(),
		center(c),
		radius(r)
	{
		material_ptr = new _PHONG();
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_SPHERE* _SPHERE::_Clone()
	{
		return (new _SPHERE(*this));
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_SPHERE& _SPHERE::operator= (const _SPHERE &sphere)
	{
		if(this == &sphere)
			return (*this);
		
		_GEOMETRICOBJECT::operator=(sphere);
		center = sphere.center;
		radius = sphere.radius;

		return (*this);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	_SPHERE::~_SPHERE() {}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool _SPHERE::_ShadowHit(const _RAY &ray, _DOUBLE &t)
	{
		_DOUBLE t_o;
		_VERTEX4F temp = _VERTEX4F(ray.origin) - center;
		_DOUBLE a = ray.vector._DotProduct(ray.vector, ray.vector);
		_DOUBLE b = 2.0 * temp._DotProduct(temp, ray.vector);
		_DOUBLE c = temp._DotProduct(temp, temp) - (radius * radius);
		_DOUBLE d = b * b - 4.0 * a * c;

		if(d < 0.0)
			return (false);
				else
		{
			double e = sqrt(d);
			double denom = 2.0 * a;
			t_o = (-b - e) / denom;    // smaller root
	
			if (t_o > kEpsilon)
			{
				t = t_o;
				return (true);
			} 
	
			t_o = (-b + e) / denom;    // larger root
	
			if (t_o > kEpsilon)
			{
				t = t_o;
				return (true);
			} 
		}
		return (false);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	bool _SPHERE::_Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr)
	{
		_DOUBLE t;
		_VERTEX4F temp = _VERTEX4F(ray.origin) - center;
		_DOUBLE a = ray.vector._DotProduct(ray.vector, ray.vector);
		_DOUBLE b = 2.0 * temp._DotProduct(temp, ray.vector);
		_DOUBLE c = temp._DotProduct(temp, temp) - (radius * radius);
		_DOUBLE d = b * b - 4.0 * a * c;

		if(d < 0.0)
			return (false);
		else
		{
			double e = sqrt(d);
			double denom = 2.0 * a;
			t = (-b - e) / denom;    // smaller root
	
			if (t > kEpsilon) {
				tmin = t;
				sr.normal 	 = (temp + _VERTEX4F(ray.vector) * t) / radius;
				sr.local_hit_point = _VERTEX4F(ray.origin) + _VERTEX4F(ray.vector) * t;
				//sr.normal = sr.local_hit_point - center;
				//sr.normal._Normalize();
				return (true);
			} 
	
			t = (-b + e) / denom;    // larger root
	
			if (t > kEpsilon) {
				tmin = t;
				sr.normal   = (temp + _VERTEX4F(ray.vector) * t) / radius;
				sr.local_hit_point = _VERTEX4F(ray.origin) + _VERTEX4F(ray.vector) * t;
				return (true);
			} 
		}
	
		return (false);
	}
}