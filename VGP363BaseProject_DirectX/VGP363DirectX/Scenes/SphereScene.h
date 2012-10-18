#pragma once
#include "Scene.h"
#include "../ThreeDee/World/World.h"

class _3DSPHERE: public _SCENE
{
public:
	ThreeD::_WORLD *world_ptr;
	ThreeD::RayCamera camera;
	
	_3DSPHERE(ThreeD::_WORLD *world);
	~_3DSPHERE();
	
	void _Draw(int *video, int w, int h);
	void _Update();
	void _Initialize();
	void _Uninitialize();
};