// Mesh.cpp
///////////////////////////////////////////////////////////////////////////

#include "Mesh.h"
#include "MeshTriangle.h"

namespace ThreeD
{
	_MESH::_MESH()
		: n_vertices(0),
		n_uvs(0),
		n_triangles(0),
		matriix(matriix._Translate(_VERTEX4F(0.0, 500.0, 500.0, 0.0)))
	{}
///////////////////////////////////////////////////////////////////////////
	_MESH::_MESH(const _MESH &m)
		: n_vertices(m.n_vertices),
		n_uvs(m.n_uvs),
		n_triangles(m.n_triangles),
		vertex_buffer(m.vertex_buffer),
		normal_buffer(m.normal_buffer),
		uv_buffer(m.uv_buffer),
		triangle_buffer(m.triangle_buffer),
		matriix(m.matriix)
	{}
///////////////////////////////////////////////////////////////////////////
	_MESH::~_MESH() {}
///////////////////////////////////////////////////////////////////////////
	_MESH& _MESH::operator=(const _MESH &m)
	{
		if(this == &m)
			return (*this);
		vertex_buffer = m.vertex_buffer;
		normal_buffer = m.normal_buffer;
		uv_buffer = m.uv_buffer;
		triangle_buffer = m.triangle_buffer;
		n_vertices = m.n_vertices;
		n_uvs = m.n_uvs;
		n_triangles = m.n_triangles;

		return (*this);
	}
///////////////////////////////////////////////////////////////////////////
	_MESH* _MESH::_Clone()
	{
		return new _MESH(*this);
	}
///////////////////////////////////////////////////////////////////////////
	bool _MESH::_Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr)
	{
		bool hiit = false;
		for(int nt = 0; nt < n_triangles; nt++)
		{
			bool hiiit = false;
			_MESHTRIANGLE tri = triangle_buffer[nt];
			hiiit = triangle_buffer[nt]._Hit(ray, tmin, sr);
			if(hiiit) hiit = true;
		}
		return hiit;
	}
///////////////////////////////////////////////////////////////////////////
	bool _MESH::_ShadowHit(const _RAY &ray, _DOUBLE &tmin)
	{
		bool hiit = false;
		for(int nt = 0; nt < n_triangles; nt++)
		{
			bool hiiit = triangle_buffer[nt]._ShadowHit(ray, tmin);
			if(hiiit) hiit = true;
		}
		return hiit;
	}
///////////////////////////////////////////////////////////////////////////

}