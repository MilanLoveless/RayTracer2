#pragma once
#include "Scene.h"
#include "../ThreeDee/Objects/GenericObject.h"
#include "../ThreeDee/Objects/SphereObject.h"
#include "../ThreeDee/World/World.h"
#include "../ThreeDee/RayTracer/Misc/HitInfo.h"
#include "../ThreeDee/RayTracer/Misc/Ray.h"
#include "../CORE/CORE.Drawing.h"
#include "../ThreeDee/Cameras/RayCamera.h"
#include "../ThreeDee/RayTracer/Tracers/RayTracer.h"

class _3DSPHERE: public _SCENE
{
public:
	ThreeD::_WORLD *world_ptr;
	ThreeD::RayCamera camera;
	ThreeD::_TRACER *tracer;
	float maxdraw;

	_3DSPHERE(ThreeD::_WORLD *world);
	~_3DSPHERE();
	
	void _Draw(int *video, int w, int h);
	void _Update();
	void _Initialize();
	void _Uninitialize();
};