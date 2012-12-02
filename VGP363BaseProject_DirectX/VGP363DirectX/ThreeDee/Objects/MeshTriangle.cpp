// MeshTriangle.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MeshTriangle.h"
#include "Mesh.h"

#define vart (_VERTEX4F(-1000.0, -2000.0, 11500.0, 0.0))
#define vurt (_VERTEX4F(0.0, 0.0, 3500.0, 0.0))


namespace ThreeD
{
	_MESHTRIANGLE::_MESHTRIANGLE()
		: _GEOMETRICOBJECT(),
		mesh_ptr(NULL),
		p0(0), p1(0), p2(0),
		n0(0), n1(0), n2(0),
		uv0(0), uv1(0), uv2(0),
		area(0.0), normal(0.0, 0.0, 1.0, 0.0)
	{}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MESHTRIANGLE::_MESHTRIANGLE(const _MESHTRIANGLE &tri)
		: _GEOMETRICOBJECT(),
		mesh_ptr(tri.mesh_ptr),
		p0(tri.p0), p1(tri.p1), p2(tri.p2),
		n0(tri.n0), n1(tri.n1), n2(tri.n2),
		uv0(tri.uv0), uv1(tri.uv1), uv2(tri.uv2)
	{
		_CalculateNormal(false);
		_CalculateTS();
		_CalculateArea();
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MESHTRIANGLE::~_MESHTRIANGLE() {}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _MESHTRIANGLE::_GetNormal()
	{
		return normal;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MESHTRIANGLE& _MESHTRIANGLE::operator= (const _MESHTRIANGLE &tri)
	{
		if(this == &tri)
			return (*this);
		
		_GEOMETRICOBJECT::operator=(tri);
		mesh_ptr = tri.mesh_ptr;
		p0 = tri.p0; p1 = tri.p1; p2 = tri.p2;
		n0 = tri.n0; n1 = tri.n1; n2 = tri.n2;
		uv0 = tri.uv0; uv1 = tri.uv1; uv2 = tri.uv2;
		normal = tri.normal;

		return (*this);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MESHTRIANGLE::_CalculateNormal(bool reversed)
	{
		normal = normal._CrossProduct(mesh_ptr->vertex_buffer[p1] - mesh_ptr->vertex_buffer[p0], mesh_ptr->vertex_buffer[p0] - mesh_ptr->vertex_buffer[p2]);
		normal._Normalize();
		if(reversed) normal = normal * -1.0;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MESHTRIANGLE::_CalculateArea()
	{
		// Heron of Alexandria's formula for the area of a triangle from Metrica (A.D. 60)
		_DOUBLE a = sqrt(pow((this->mesh_ptr->vertex_buffer[p0].x - this->mesh_ptr->vertex_buffer[p1].x), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p0].y - this->mesh_ptr->vertex_buffer[p1].y), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p0].z - this->mesh_ptr->vertex_buffer[p1].z), 2));
		_DOUBLE b = sqrt(pow((this->mesh_ptr->vertex_buffer[p0].x - this->mesh_ptr->vertex_buffer[p2].x), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p0].y - this->mesh_ptr->vertex_buffer[p2].y), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p0].z - this->mesh_ptr->vertex_buffer[p2].z), 2));
		_DOUBLE c = sqrt(pow((this->mesh_ptr->vertex_buffer[p1].x - this->mesh_ptr->vertex_buffer[p2].x), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p1].y - this->mesh_ptr->vertex_buffer[p2].y), 2) 
					   + pow((this->mesh_ptr->vertex_buffer[p1].z - this->mesh_ptr->vertex_buffer[p2].z), 2));
		_DOUBLE s = (a + b + c) * 0.5;
		this->area = sqrt(s*(s-a)*(s-b)*(s-c));
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _MESHTRIANGLE::_InterpolateNormal(const _DOUBLE beta, const _DOUBLE gamma)
	{
		_VERTEX4F normal((this->mesh_ptr->normal_buffer[n0] * (1.0 - beta - gamma)) + (this->mesh_ptr->normal_buffer[n1] * beta) + (this->mesh_ptr->normal_buffer[n2] * gamma));
		normal._Normalize();
		return normal;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_POINT2D _MESHTRIANGLE::_InterpolateUV(const _DOUBLE beta, const _DOUBLE gamma)
	{
		return((this->mesh_ptr->uv_buffer[uv0] * (1.0 - beta - gamma))
			 + (this->mesh_ptr->uv_buffer[uv1] * beta)
			 + (this->mesh_ptr->uv_buffer[uv2] * gamma));
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_MESHTRIANGLE* _MESHTRIANGLE::_Clone()
	{
		return new _MESHTRIANGLE(*this);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool _MESHTRIANGLE::_Hit(const _RAY &ray, _DOUBLE &tmin, _SHADEREC &sr)
	{
		_VERTEX4F v0 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p0]) + vurt;
		_VERTEX4F v1 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p1]) + vurt;
		_VERTEX4F v2 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p2]) + vurt;
		
		// X Components
		_DOUBLE a = v0.x - v1.x;
		_DOUBLE b = v0.x - v2.x;
		_DOUBLE c = ray.vector.x;
		_DOUBLE d = v0.x - ray.origin.x;
		// Y Components
		_DOUBLE e = v0.y - v1.y;
		_DOUBLE f = v0.y - v2.y;
		_DOUBLE g = ray.vector.y;
		_DOUBLE h = v0.y - ray.origin.y;
		// Z Components
		_DOUBLE i = v0.z - v1.z;
		_DOUBLE j = v0.z - v2.z;
		_DOUBLE k = ray.vector.z;
		_DOUBLE l = v0.z - ray.origin.z;

		_DOUBLE m = f * k - g * j;
		_DOUBLE n = h * k - g * l;
		_DOUBLE p = f * l - h * j;
		_DOUBLE q = g * i - e * k;
		_DOUBLE s = e * j - f * i;

		_DOUBLE inv_denominator = 1.0 / (a * m + b * q + c * s);
		_DOUBLE e1 = d * m - b * n - c * p;
		_DOUBLE beta = e1 * inv_denominator;

		if (beta < 0.0) return false;

		_DOUBLE r = e * l - h * i;
		_DOUBLE e2 = a * n + d * q + c * r;
		_DOUBLE gamma = e2 * inv_denominator;

		if (gamma < 0.0) return false;
		if (beta + gamma > 1.0) return false;

		_DOUBLE e3 = a * p - b * r + d * s;
		_DOUBLE t = e3 * inv_denominator;
		
		if(t < kEpsilon) return false;
		if(t >= tmin) return false;
		tmin = t;
		//sr.normal = mesh_ptr->matriix._Multiply(_InterpolateNormal(beta, gamma));
		_LightingCalculation(sr, beta, gamma);
		sr.local_hit_point = _VERTEX4F(ray.origin) + (_VERTEX4F(ray.vector) * t);
		//sr.hit_UV = _InterpolateUV(beta, gamma);
		return true;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool _MESHTRIANGLE::_ShadowHit(const _RAY &ray, _DOUBLE &tmin)
	{
		_VERTEX4F v0 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p0]) + vurt;
		_VERTEX4F v1 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p1]) + vurt;
		_VERTEX4F v2 = mesh_ptr->matriix._Multiply(this->mesh_ptr->vertex_buffer[this->p2]) + vurt;
		
		// X Components
		_DOUBLE a = v0.x - v1.x;
		_DOUBLE b = v0.x - v2.x;
		_DOUBLE c = ray.vector.x;
		_DOUBLE d = v0.x - ray.origin.x;
		// Y Components
		_DOUBLE e = v0.y - v1.y;
		_DOUBLE f = v0.y - v2.y;
		_DOUBLE g = ray.vector.y;
		_DOUBLE h = v0.y - ray.origin.y;
		// Z Components
		_DOUBLE i = v0.z - v1.z;
		_DOUBLE j = v0.z - v2.z;
		_DOUBLE k = ray.vector.z;
		_DOUBLE l = v0.z - ray.origin.z;

		_DOUBLE m = f * k - g * j;
		_DOUBLE n = h * k - g * l;
		_DOUBLE p = f * l - h * j;
		_DOUBLE q = g * i - e * k;
		_DOUBLE s = e * j - f * i;

		_DOUBLE inv_denominator = 1.0 / (a * m + b * q + c * s);
		_DOUBLE e1 = d * m - b * n - c * p;
		_DOUBLE beta = e1 * inv_denominator;

		if (beta < 0.0) return false;

		_DOUBLE r = e * l - h * i;
		_DOUBLE e2 = a * n + d * q + c * r;
		_DOUBLE gamma = e2 * inv_denominator;

		if (gamma < 0.0) return false;
		if (beta + gamma > 1.0) return false;

		_DOUBLE e3 = a * p - b * r + d * s;
		_DOUBLE t = e3 * inv_denominator;
		
		if(t < kEpsilon) return false;
		
		tmin = t;
		return true;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _MESHTRIANGLE::_LightingCalculation(_SHADEREC &sr, const _DOUBLE beta, const _DOUBLE gamma)
	{
		sr.hit_UV = ((this->mesh_ptr->uv_buffer[uv0] * (1.0 - beta - gamma))
			 + (this->mesh_ptr->uv_buffer[uv1] * beta)
			 + (this->mesh_ptr->uv_buffer[uv2] * gamma));
		sr.normal =  _VERTEX4F((this->mesh_ptr->normal_buffer[n0] * (1.0 - beta - gamma)) + (this->mesh_ptr->normal_buffer[n1] * beta) + (this->mesh_ptr->normal_buffer[n2] * gamma));
		sr.normal._Normalize();
		sr.binormal = sr.binormal._CrossProduct(sr.normal, tangent);
		sr.binormal._Normalize();
		sr.tangent = sr.tangent._CrossProduct(sr.normal, sr.binormal);
		sr.tangent._Normalize();
		sr.normal = mesh_ptr->matriix._Multiply(sr.normal);
		sr.binormal = mesh_ptr->matriix._Multiply(sr.binormal);
		sr.tangent = mesh_ptr->matriix._Multiply(sr.tangent);
	}

	void _MESHTRIANGLE::_CalculateTS()
	{
		_VERTEX4F D = (mesh_ptr->vertex_buffer[p1] - mesh_ptr->vertex_buffer[p0]);
		_VERTEX4F E = (mesh_ptr->vertex_buffer[p2] - mesh_ptr->vertex_buffer[p0]);
		_POINT2D F = (mesh_ptr->uv_buffer[uv1] + (mesh_ptr->uv_buffer[uv0] * -1.0));
		_POINT2D G = (mesh_ptr->uv_buffer[uv2] + (mesh_ptr->uv_buffer[uv0] * -1.0));

		_DOUBLE inv_det = 1.0 / (F.x * G.y - F.y * G.x);

		tangent = _VERTEX4F(D.x * G.y - E.x * F.y, D.y * G.y - E.y * F.y, D.z * G.y - E.z * F.y, 0.0) * inv_det;
		tangent = tangent - normal * normal._DotProduct(normal, tangent);
		binormal = _VERTEX4F(E.x * F.x - D.x * G.x, E.y * F.x - D.y * G.x, E.z * F.x - D.z * G.x, 0.0) * inv_det;
		binormal = binormal - normal * normal._DotProduct(normal, binormal) - tangent * tangent._DotProduct(tangent, binormal) / tangent._DotProduct(tangent, tangent);
		tangent._Normalize();
		binormal._Normalize();
	}
}