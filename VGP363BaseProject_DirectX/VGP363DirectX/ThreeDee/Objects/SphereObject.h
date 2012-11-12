// SphereObject.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GeometricObject.h"
#include "../RayTracer/Materials/Phong.h"
#include "../RayTracer/Materials/Matte.h"
#include"../RayTracer/Materials/IridescentPhong.h"

namespace ThreeD
{
	class _SPHERE : public _GEOMETRICOBJECT
	{
	public:
		_SPHERE();
		~_SPHERE();
		_SPHERE(_VERTEX4F center, _DOUBLE r);
		virtual _SPHERE* _Clone();
		_SPHERE& operator= (const _SPHERE &sphere);

		void _SetCenter(const _VERTEX4F &c);
		void _SetRadius(const _DOUBLE r);
		virtual bool _Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &s);
		virtual bool _ShadowHit(const _RAY &ray, _DOUBLE &t);

		_VERTEX4F center;
		_DOUBLE radius;
		static const _DOUBLE kEpsilon;
	};
}