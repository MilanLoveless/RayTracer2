//Primitives.cpp
////////////////////////////////////////////////////////////////////////////////////

#include "Primitives.h"

namespace ThreeD
{
	double ClampIt(double ins)
	{
		if(ins<0.0) ins = 0.0;
		if(ins>1.0) ins = 1.0;
		return ins;
	}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	double vMax(double v0, double v1, double v2)
	{
		double maxi = v0;
		if(maxi < v1)
		{
			maxi = v1;
		}
		if(maxi < v2)
		{
			maxi = v2;
		}

		return maxi;
	}

	double vMin(double v0, double v1, double v2)
	{
		double mini = v0;
		if(mini > v1)
		{
			mini = v1;
		}
		if(mini > v2)
		{
			mini = v2;
		}
		return mini;
	}

	#define f12(xx, yy) ((v1.y - v2.y) * (xx) + (v2.x - v1.x) * (yy) + v1.x * v2.y - v2.x * v1.y)
	#define f20(xx, yy) ((v2.y - v0.y) * (xx) + (v0.x - v2.x) * (yy) + v2.x * v0.y - v0.x * v2.y)
	#define f01(xx, yy) ((v0.y - v1.y) * (xx) + (v1.x - v0.x) * (yy) + v0.x * v1.y - v1.x * v0.y)

	void _SHASH_ALG(double *zb, int *video, int w, int h, _VERTEX4F v0, _VERTEX4F v1, _VERTEX4F v2, int xmin, int xmax, int ymin, int ymax, _COLOR4F c0, _COLOR4F c1, _COLOR4F c2)
	{
		for(int y = ymin; y <= ymax; y++)
		{
			for(int x = xmin; x <= xmax; x++)
			{
				double alpha = f12(x, y)/f12(v0.x, v0.y);
				double beta = f20(x, y)/f20(v1.x, v1.y);
				double gamma = f01(x, y)/f01(v2.x, v2.y);
				if(alpha >= 0 && beta >= 0 && gamma >= 0)
				{
					if(zb != NULL)
					{
						double z = alpha*v0.z + beta*v1.z + gamma*v2.z;
						if(zb[y*w+x] < z) continue;
						zb[y*w+x] = z;
					}
					// Milan's iridescent shader - a creative use of Rodrigues' Rotation Formula (1840 AD)
					///////////////////////////////////////////////////////////////////////
					_VERTEX4F v01 = v1 - v0;
					_VERTEX4F v02 = v2 - v0;
					_VERTEX4F snorm = v01._CrossProduct(v02, v01); //surface normal
					snorm._Normalize();

					_VERTEX4F posi((double)x, (double) y, alpha*v0.z + beta*v1.z + gamma*v2.z, 1.0); // Use screen X and Y and Barycentric Coordinates to determin the Z Depth for the position Coordinate
					_VERTEX4F vLight = posi - _VERTEX4F(400.0, 200.0, -200.0, 1.0); // Object to Light Vector
					vLight._Normalize();
					_VERTEX4F camera1(w/2.0, h/2.0, -200.0, 0.0);
					_VERTEX4F cameraV = (camera1 - posi); // Object to Camera Vector
					cameraV._Normalize();
					
					_VERTEX4F k(1.0, 1.0, 1.0, 0.0); // the reference vector, we will be 'rotating' our base color around this point (1.0 r 1.0 g 1.0 b is white, the center of the color wheel of course!?)		
					k._Normalize();
					double theta = cameraV._DotProduct(cameraV, snorm);
					_VERTEX4F v(0.5, 0.9, 0.1, 0.0); // a color masquerading as a vector!!? madness!
					// ready? ok, here it is!
					_VERTEX4F IRI = (v*cos(theta) + (k._CrossProduct(k, v))*sin(theta)) + (k*(k._DotProduct(k, v))) * (1 - cos(theta));

					// Phong Shader
					_VERTEX4F vReflection = (cameraV - (snorm * 2.0 * snorm._DotProduct(snorm, cameraV)));
					double fSpecular = ClampIt(vReflection._DotProduct(vLight, vReflection));
					double fLambert = ClampIt(vLight._DotProduct(vLight, snorm));
					IRI.x = 255.0 * ClampIt((IRI.x * fLambert) + pow((double)fSpecular, 5.0) + 0.05); // Red
					IRI.y = 255.0 * ClampIt((IRI.y * fLambert) + pow((double)fSpecular, 5.0) + 0.05); // Green
					IRI.z = 255.0 * ClampIt((IRI.z * fLambert) + pow((double)fSpecular, 5.0) + 0.05); // Blue

					int color = CORE::_CreateColor(255, (int)IRI.x, (int)IRI.y, (int)IRI.z);
					CORE::_PutPixel(video, w, h, x, y, color);
				}
			}
		}
	}

	void _DrawTriangle(float *zb, int *video, int w, int h, _VERTEX4F v0, _VERTEX4F v1, _VERTEX4F v2, _COLOR4F c0, _COLOR4F c1, _COLOR4F c2)
	{
		int xmin = (int)vMin(v0.x, v1.x, v2.x);
		int xmax = (int)vMax(v0.x, v1.x, v2.x);
		int ymin = (int)vMin(v0.y, v1.y, v2.y);
		int ymax = (int)vMax(v0.y, v1.y, v2.y);
		
		if(xmin < 0) xmin = 0;
		if(xmax < 0) xmax = 0;
		if(xmax > w - 1) xmax = w - 1;
		if(xmin >= xmax) return;
		if(ymin < 0) ymin = 0;
		if(ymax < 0) ymax = 0;
		if(ymax > h - 1) ymax = h - 1;
		if(ymin >= ymax) return;
		_VERTEX4F v01 = v1 - v0;
		_VERTEX4F v02 = v2 - v0;
		_VERTEX4F snorm = v01._CrossProduct(v02, v01); //surface normal
		snorm._Normalize();
		if(snorm._DotProduct(_VERTEX4F(0.0, 0.0, 1.0, 0.0), snorm) < 0.0) return;	

		_SHASH_ALG(zb, video, w, h, v0, v1, v2, xmin, xmax, ymin, ymax, c0, c1, c2);
	}
	*/
}