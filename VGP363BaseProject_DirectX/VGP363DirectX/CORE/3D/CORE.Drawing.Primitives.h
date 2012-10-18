// CORE.Drawing.Primitives.h
/////////////////////////////////////////////////////////////////////////

#ifndef __CORE_DRAWING_PRIMITIVES_H_
#define __CORE_DRAWING_PRIMITIVES_H_

#include "CORE.Matrix.h"

namespace GameCore {

	#ifndef NULL
	#define NULL ((void*)0)
	#endif

	///////////////////////////////////////////////////////////////////////////////////
	// Render Settings

	typedef int RENDER_MODE;
	#define R_MATRIX (1<<0)     // Apply a matrix transform when rendering triangles
	#define R_ZBUFFER (1<<1)	// Consider the Z-Buffer when plotting pixels
	#define R_COLOR (1<<2)		// Use the vertex color channel for coloring pixels
	#define R_TEXTURE (1<<3)	// Use the texture channel when coloring pixels
	#define R_GOURAUD (1<<4)	// Use gouraud shading wherever possible (faster)
	#define R_PHONG (1<<5)		// Use phong shading wherever possible (default)
	#define R_BUMPMAP (1<<6)    // Determine lighting information from bump map

	///////////////////////////////////////////////////////////////////////////////////
	// Geometric Primitives

	class Color3D { 
	public:
		double r, g, b, a;

		void _Set(double dr, double dg, double db, double da);
		static Color3D _Create(double dr, double dg, double db, double da);
		static void _AlphaBlend(double alpha, double &r1, double &g1, double &b1, double r2, double g2, double b2);
	};

	class Point3D
	{
	public:
		double x, y, z, w;
		static Point3D _Create(double dx, double dy, double dz, double dw);
		static Point3D _CrossProduct(const Point3D &a, const Point3D &b);
		static Point3D _CreateVector(const Point3D &a, const Point3D &b);
		static Point3D _SurfaceNormal(const Point3D &a, const Point3D &b, const Point3D &c);
		static double _DotProduct(const Point3D &a, const Point3D &b);
		static Point3D _Reflection(const Point3D &vector, const Point3D &normal); 

		void _ApplyCameraSpaceProjection(Matrix3D *m, int width, int height);
		void _Set(double dx, double dy, double dz, double dw);
		void _Translate(double dx, double dy, double dz, double dw);
		void _Add(const Point3D& vector); // Vector or point addition
		void _Subtract(const Point3D& vector); // Vector or point subtraction
		void _Divide(double val); // Scalar division
		void _Multiply(double val); // Scalar multiplication
		void _Homogenize();
		void _Normalize();
		double _Length();
	};

	class TextureCoord3D
	{
	public:
		double tu, tv;
	};

	class Triangle3D
	{
	public:
		// Three vertex indices into a vertex buffer ///////////////////////
		int a, b, c;

		// Three UV indices into a UV buffer ///////////////////////////////
		int auv, buv, cuv;

		// Surface normal of triangle //////////////////////////////////////
		Point3D surface_normal;

		////////////////////////////////////////////////////////////////////
		// Utility Functions:
		static void _ComputeSurfaceNormals(int num_v, Point3D vb[], int num_i, Triangle3D ib[]);
		static void _ComputeVertexNormals(int num_vn, Point3D vn[], int num_v, Point3D vb[], int num_i, Triangle3D ib[]);
		void _SetUV(int nAuv, int nBuv, int nCuv) { this->auv = nAuv; this->buv = nBuv; this->cuv = nCuv; }
	};

	class Mesh3D {
	public:
		// Index Buffer ////////////////////////////////////////////////////
		int num_i;
		Triangle3D *ib;

		// Vertex Buffer ///////////////////////////////////////////////////
		int num_v;
		Point3D *vb;

		// Vertex Normal Buffer ////////////////////////////////////////////
		int num_vn;
		Point3D *vn;

		// Color Channel ///////////////////////////////////////////////////
		int num_c;
		Color3D *cb;

		// UV Channel //////////////////////////////////////////////////////
		int num_uv;
		TextureCoord3D *uv;

		////////////////////////////////////////////////////////////////////
		// Texture Channels
		// Channel 1 used for base color
		int w1, h1;              // Width,Height of Texture Channel 1
		int *pT1;				 // Pixel data of Texture Channel 1
		// Channel 2 used for bump map
		int w2, h2;              // Width,Height of Texture Channel 2
		int *pT2;				 // Pixel data of Texture Channel 2
		////////////////////////////////////////////////////////////////////

		RENDER_MODE rmode;
	};

	typedef int LIGHTING_MODE;
	#define L_FACET (1<<0)		 // Faceted lighting
	#define L_SMOOTH (1<<1)		 // Smooth lighting
	#define L_AMBIENT (1<<2)	 // The light is ambient (e.g. glow from everywhere)
	#define L_DIRECTIONAL (1<<3) // The light is directed globally everywhere in a particular direction
	#define L_POINTLIGHT (1<<4)  // The light radiates outward from a point
	#define L_DIFFUSE (1<<5)     // The point light exhibits diffuse shading
	#define L_SPECULAR (1<<6)    // The point light exhibits specular shading
	#define L_FALLOFF1 (1<<7)    // The shading model utilizes easing functions
	#define L_FALLOFF2 (1<<8)   // The shading model utilizes easing functions
	#define L_FALLOFF3 (1<<9)   // The shading model utilizes easing functions

	class Light3D {
	public:
		Point3D position;		 // The position of the light in world space if it is a positionable light
		Point3D direction;	 // The direction that the light is facing in world space if applicable
		double intensity;		 // The intensity of the light
		Color3D color;			 // The color that the light emits, e.g. white, blue, etc.
		LIGHTING_MODE lmode;	 // The lighting mode that determines how the light is rendered

		// Function used to apply the light to a given point
		virtual void _ApplyToPixel(
			// These are the barycentric coordinates of the point being lit
			double alpha, double beta, double gamma,
			// This is the mesh and triangle that the point is in
			Mesh3D* pMesh, Triangle3D *pTriangle,
			// These are the coordinates of the point in camera space
			const Point3D &pt,
			// The surface normal of the surface the point is on
			const Point3D &lighting_normal,
			// The vertex normals of the triangle that the point is in
			const Point3D &v0n,
			const Point3D &v1n,
			const Point3D &v2n,
			// The base color of the point being lit
			double &r, double &g, double &b, double &a
		);

		virtual void _ApplyToVertex(
			// This is the mesh and triangle that the point is in
			Mesh3D* pMesh, Triangle3D *pTriangle,
			// These vertex being lit
			const Point3D &pt,
			// The surface normal of triangle the vertex is in
			const Point3D &lighting_normal,
			// The vertex normal of the vertex being lit
			const Point3D &vn,
			// The net color of light on the vertex
			double &r, double &g, double &b, double &a,
			// The net intensity of light on the vertex
			double &net_i
		);
	};

	class Scene3D {
	public:
		int num_m;
		Mesh3D** meshes;

		int num_l;
		Light3D** lights;
	public:
		// Precalculated lighting information /////////////////////
		double ambience;    // Ambient light can be precalculated 
	};

	//////////////////////////////////////////////////////////////////////////////////
	// Primitive Drawing and Color Operations

	#define _PUTPIXEL(p, x, y, width, height, value) ((p)[((y)*(width))+(x)]=(value))

	#define _COLOR32_RGBA(r,g,b,a) ((((int)(r))<<24)+(((int)(g))<<16)+(((int)(b))<<8)+((int)(a)))
	#define _COLOR32_ARGB(a,r,g,b) ((((int)(a))<<24)+(((int)(r))<<16)+(((int)(g))<<8)+((int)(b)))
	#define _COLOR32_ARGB_GET_RED(c) ((((unsigned int)(c))&0x00FF0000)>>16)
	#define _COLOR32_ARGB_GET_GREEN(c) ((((unsigned int)(c))&0x0000FF00)>>8)
	#define _COLOR32_ARGB_GET_BLUE(c) ((((unsigned int)(c))&0x000000FF))
	#define _COLOR32_ARGB_GET_ALPHA(c) ((((unsigned int)(c))&0xFF000000)>>24)

	#define _COLOR_BLACK _COLOR32_ARGB(255,0,0,0)

	///////////////////////////////////////////////////////////////////////////////////
	// Render Functions

	class Matrix3D;
	void _DrawTriangle(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene, Mesh3D *pMesh, int nTriangleIndex);	
	void _DrawTriangleList(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene, Mesh3D *pMesh);
	void _DrawTriangleList(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene);

	void _ClearZBuffer(double *pZBuffer, int nWidth, int nHeight);

}

#endif