#pragma once
#include "Scene.h"
#include "../ThreeDee/World/World.h"

class _3DSCENE: public _SCENE
{
public:
	ThreeD::_WORLD *world;
	bool rasterize;
	virtual void _Draw(int *video, int w, int h) = 0;
	virtual void _Update() = 0;
	virtual void _Initialize() = 0;
	virtual void _Uninitialize() = 0;
};
