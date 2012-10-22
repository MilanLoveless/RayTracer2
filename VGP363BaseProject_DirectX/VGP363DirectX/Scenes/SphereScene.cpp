// SphereScene.cpp
////////////////////////////////////////////////////////
#include "SphereScene.h"


_3DSPHERE::_3DSPHERE(ThreeD::_WORLD *world)
{
	world_ptr = world;
	tracer = new ThreeD::_TRACER(world);
}

_3DSPHERE::~_3DSPHERE()
{
	delete tracer;
	tracer = NULL;
}

void _3DSPHERE::_Draw(int *video, int w, int h)
{
	for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			ThreeD::_RAY px = camera._CreateRay(x, y);
			ThreeD::_HITINFO xc;
			double  maxd = 1000000.0;
			ThreeD::_COLOR4F col = tracer->_TraceRay(px, maxd, xc);
			int c = CreateColor((int)(col.a*255.0), (int)(col.r*255.0), (int)(col.g*255.0), (int)(col.b*255.0)); 
			video[y*w+x] = c;
		}
	}
}

void _3DSPHERE::_Update()
{

}

void _3DSPHERE::_Initialize()
{
	world_ptr->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(0.0, 0.0, 2100.0, 1.0), 250.0, ThreeD::_COLOR4F(1.0, 0.3, 0.9, 0.2)));
	world_ptr->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(0.0, 0.0, 2000.0, 1.0), 250.0, ThreeD::_COLOR4F(1.0, 0.9, 0.2, 0.3)));
}

void _3DSPHERE::_Uninitialize()
{

}

