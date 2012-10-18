// Mesh.h
/////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "Vertex.h"
#include "Matrix.h"

namespace ThreeD
{
	class _TRIANGLE3I
	{
	public:
		int a, b, c;
		int auv, buv, cuv;
		_VERTEX4F surface_normal;
	};
/////////////////////////////////////////////////////////////////////////////
	class _UV2F
	{
	public:
		double tu, tv;
	};
/////////////////////////////////////////////////////////////////////////////
	class _MESH
	{
	public:
		//triangle index buffer
		int num_i;
		_TRIANGLE3I *ib;
		
		//vertex buffer
		int num_v;
		_VERTEX4F *vb;
		
		//vertex normal buffer
		int num_vn;
		_VERTEX4F *vn;

		//uv channel
		int num_uv;
		_UV2F *uv;

		///////////////////////////////////////////////
		//texture channels
		//int num_textures;
		//int *pTW, *pTH; //Width, Height of Texture Channels
		//int **ppT; //Pixel data of Texture Channels
		///////////////////////////////////////////////

		int render_settings;
	};
}