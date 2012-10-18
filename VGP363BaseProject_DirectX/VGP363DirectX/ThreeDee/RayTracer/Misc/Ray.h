#pragma once
#include "../../Components/Vertex.h"

namespace ThreeD
{
	class _RAY
	{
	public:
		_VERTEX4F origin;
		_VERTEX4F vector;

		_RAY();
		~_RAY();
		_RAY(const _VERTEX4F &point, const _VERTEX4F &dir);
		_RAY(const _RAY &r);
		_RAY& _RAY::operator = (const _RAY &r);
		_RAY _Reflect(const _VERTEX4F &v);
	};
}