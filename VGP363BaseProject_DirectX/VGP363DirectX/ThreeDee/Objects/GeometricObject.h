// GeometricObject.h
///////////////////////////////////////////////////////////////////////////////

#pragma once 

#include <math.h>

#include "../Components/Constants.h"
#include "../Components/Vertex.h"
#include "../RayTracer/Misc/Ray.h"
#include "../RayTracer/Misc/ShadeRec.h"

namespace ThreeD
{
	class _MATERIAL;
	class _GEOMETRICOBJECT
	{
	public:
		_GEOMETRICOBJECT();
		_GEOMETRICOBJECT(const _GEOMETRICOBJECT &obj);
		virtual _GEOMETRICOBJECT* _Clone() = 0;
		~_GEOMETRICOBJECT();
		_GEOMETRICOBJECT& operator= (const _GEOMETRICOBJECT &obj);

		virtual bool _Hit(const _RAY &ray, _DOUBLE &t, _SHADEREC &s) = 0;
		void _SetMaterial(_MATERIAL *m_ptr);
		_MATERIAL* _GetMaterial();
		//virtual void _SetBoundingBox();
		//virtual _BBOX _GetBoundingBox();
		virtual _VERTEX4F _Sample();
		virtual _DOUBLE _PDF(_SHADEREC &sr);
		virtual _VERTEX4F _GetNormal();
		virtual _VERTEX4F _GetNormal(const _VERTEX4F &p);
		mutable _MATERIAL *material_ptr;
		bool shadows;
	};
}