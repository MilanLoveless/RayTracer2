// Pinhole.h
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Camera.h"
#include "../RayTracer/Misc/Point2D.h"

namespace ThreeD
{
	class _PINHOLE : public _CAMERA
	{
	public:
		_PINHOLE();
		_PINHOLE(const _PINHOLE &ph);
		~_PINHOLE();
		_PINHOLE& operator= (const _PINHOLE &ph);

		void _SetFOV(const _DOUBLE fov);
		void _SetZoom(const _DOUBLE zooom);
		_RAY _GetDirection(const _POINT2D &p);
		virtual void _RenderScene(const _WORLD &w);

		_DOUBLE d;
		_DOUBLE zoom;
	};
}