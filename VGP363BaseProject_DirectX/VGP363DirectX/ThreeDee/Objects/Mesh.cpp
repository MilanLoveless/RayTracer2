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
		matriix(matriix._RotateY(22.5))
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
		_DOUBLE t = tmin;
		//_DOUBLE t = kHugeValue;
		_VERTEX4F normal;
		_VERTEX4F local_hit_point;

		for(int nt = 0; nt < n_triangles; nt++)
		{
			if (triangle_buffer[nt]._Hit(ray, tmin, sr))
			{
				if(tmin < t)
				{
					sr.hit_an_object = true;
					t = tmin;
					sr.material_ptr = material_ptr;
					sr.hit_point = _VERTEX4F(ray.origin) + _VERTEX4F(ray.vector) * t;
					normal = sr.normal;
					local_hit_point = sr.local_hit_point;
					hiit = true;
				}
			}
		}
		/*if(hiit)
		{
			sr.t = t;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
		}*/
		return hiit;
	}
///////////////////////////////////////////////////////////////////////////
	bool _MESH::_ShadowHit(const _RAY &ray, _DOUBLE &tmin)
	{
		bool hiit = false;
		_DOUBLE t = tmin;
		for(int nt = 0; nt < n_triangles; nt++)
		{
			if(triangle_buffer[nt]._ShadowHit(ray, t))
			{
				hiit = true;
			}
		}
		return hiit;
	}
///////////////////////////////////////////////////////////////////////////

}