// MeshTriangle.h
////////////////////////////////////////////////////////////////////

#pragma once

#include "../Components/Vertex.h"
#include "../Components/Constants.h"
#include "../RayTracer/Misc/Ray.h"
#include "GeometricObject.h"

namespace ThreeD
{
	class _MESHTRIANGLE : public _GEOMETRICOBJECT
	{
	public:
		int p0, p1, p2;
		int uv0, uv1, uv2;
		_VERTEX4F normal;
		_DOUBLE area;

		_MESHTRIANGLE();
		_MESHTRIANGLE(const int v0, const int v1, const int v2, const int t0, const int t1, const int t2);
		virtual _MESHTRIANGLE* _Clone() = 0;
		_MESHTRIANGLE(const _MESHTRIANGLE &tri);
		~_MESHTRIANGLE();
		_MESHTRIANGLE& operator= (const _MESHTRIANGLE &tri);
		virtual bool _Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr) = 0;
		virtual bool _ShadowHit(const _RAY &ray, _DOUBLE &tmin);
		void _CalculateNormal(bool reversed);
		virtual _VERTEX4F _GetNormal();
		float _GetU(const _DOUBLE beta, const _DOUBLE gamma);
		float _GetV(const _DOUBLE beta, const _DOUBLE gamma);
		_POINT2D _GetUV(_SHADEREC &sr);
	};
}