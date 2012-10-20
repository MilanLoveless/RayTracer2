// SphereScene.cpp
////////////////////////////////////////////////////////
#include "SphereScene.h"


_3DSPHERE::_3DSPHERE(ThreeD::_WORLD *world)
{
	world_ptr = world;
}

_3DSPHERE::~_3DSPHERE()
{

}

void _3DSPHERE::_Draw(int *video, int w, int h)
{
	for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			ThreeD::_RAY px = camera._CreateRay(x, y);
			ThreeD::_HITINFO xc;

			int c = CreateColor((int)(xc.hitcolor.a*255.0), (int)(xc.hitcolor.r*255.0), (int)(xc.hitcolor.g*255.0), (int)(xc.hitcolor.b*255.0)); 
			video[y*h+x] = c;
		}
	}
}

void _3DSPHERE::_Update()
{

}

void _3DSPHERE::_Initialize()
{
	world_ptr->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(0.0, 0.0, 500, 1.0), 250.0, ThreeD::_COLOR4F(1.0, 0.9, 0.2, 0.3));
}

void _3DSPHERE::_Uninitialize()
{

}

