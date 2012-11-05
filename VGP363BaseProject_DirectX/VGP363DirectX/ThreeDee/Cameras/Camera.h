// Camera.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Components/Vertex.h"
#include "../Components/Matrix.h"
#include "../World/World.h"
#include "../Components/Constants.h"

namespace ThreeD
{
	class _CAMERA
	{
	public:
		_CAMERA();
		_CAMERA(const _CAMERA &c);
		~_CAMERA();

		virtual void _RenderScene(const _WORLD &w) = 0;

		void _SetPos(const _VERTEX4F &p);
		void _SetPos(const _DOUBLE x1, const _DOUBLE y1, const _DOUBLE z1);
		void _SetMatrix(const _MATRIX16F &m1);
		void _SetExposure(const _DOUBLE exp);
		_CAMERA& operator= (const _CAMERA &c);

		_VERTEX4F iposition;
		_VERTEX4F ifacing;
		_MATRIX16F transformM16;
		_DOUBLE exposure_time;
	};
}