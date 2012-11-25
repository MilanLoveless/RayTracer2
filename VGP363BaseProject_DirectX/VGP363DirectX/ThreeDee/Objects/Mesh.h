// Mesh.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include "../Components/Vertex.h"
#include "../RayTracer/Misc/Point2D.h"
#include "../Components/Matrix.h"
#include "MeshTriangle.h"
#include "GeometricObject.h"

namespace ThreeD
{
	class _MESHTRIANGLE;
	class _MESH : public _GEOMETRICOBJECT
	{
	public:
		std::vector<_VERTEX4F> vertex_buffer;
		std::vector<_VERTEX4F> normal_buffer;
		std::vector<_POINT2D> uv_buffer;
		std::vector<_MESHTRIANGLE> triangle_buffer;
		int n_triangles, n_vertices, n_uvs;
		_MATRIX16F matriix;
		//insert bounding box here

		_MESH();
		_MESH(const _MESH &m);
		~_MESH();
		_MESH* _Clone();
		_MESH& operator= (const _MESH &m);
		virtual bool _Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr);
		virtual bool _ShadowHit(const _RAY &ray, _DOUBLE &tmin);
		//virtual void _SetBoundingBox();
		//virtual _BBOX _GetBoundingBox();
		//virtual _VERTEX4F _Sample();
		//virtual _DOUBLE _PDF(_SHADEREC &sr);
		//virtual _VERTEX4F _GetNormal();
		//virtual _VERTEX4F _GetNormal(const _VERTEX4F &p);
	};
}