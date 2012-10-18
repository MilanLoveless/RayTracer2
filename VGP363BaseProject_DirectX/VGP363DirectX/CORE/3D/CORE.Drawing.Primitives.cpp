// CORE.Primitives.cpp
/////////////////////////////////////////////////////////////////////////////////////

#include "..\..\GameCore.h"

#include <math.h>

namespace GameCore {

	void Color3D::_Set(double dr, double dg, double db, double da) { 
		r = dr; g = dg; b = db; a = da;
	}

	Color3D Color3D::_Create(double dr, double dg, double db, double da) { 
		Color3D color;
		color._Set(dr, dg, db, da);
		return color;
	}

	void Color3D::_AlphaBlend(double alpha, double &r1, double &g1, double &b1, double r2, double g2, double b2) {
		// Take one of the colors along the vector between the colors
		// by the distance given by alpha...
		r1 = r1 + alpha * (r2 - r1);
		g1 = g1 + alpha * (g2 - g1);
		b1 = b1 + alpha * (b2 - b1);
	}

	void Point3D::_Set(double dx, double dy, double dz, double dw) {
		x = dx;
		y = dy;
		z = dz;
		w = dw;
	}

	Point3D Point3D::_Create(double dx, double dy, double dz, double dw) {
		Point3D result;
		result._Set(dx, dy, dz, dw);
		return result;
	}

	void Point3D::_Translate(double dx, double dy, double dz, double dw) {
		x += dx;
		y += dy;
		z += dz;
		w += dw;
	}
	
	double Point3D::_DotProduct(const Point3D &a, const Point3D &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
		//return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	Point3D Point3D::_Reflection(const Point3D &vector, const Point3D &normal) {
		// R = V - 2(V.N)*N
		float coefficient = 2.0 * Point3D::_DotProduct(vector, normal);
		Point3D temp1 = normal;
		temp1._Multiply(coefficient);
		Point3D result = vector;
		result._Subtract(temp1);
		return result;
	}

	Point3D Point3D::_CrossProduct(const Point3D &a, const Point3D &b) {
		Point3D result;
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
		result.w = 0.0;
		return result;
	}

	Point3D Point3D::_CreateVector(const Point3D &a, const Point3D &b) {
		Point3D result;
		result.x = b.x - a.x;
		result.y = b.y - a.y;
		result.z = b.z - a.z;
		result.w = 0.0;
		return result;
	}

	Point3D Point3D::_SurfaceNormal(const Point3D &a, const Point3D &b, const Point3D &c) {
		Point3D v1 = Point3D::_CreateVector(a, b);
		Point3D v2 = Point3D::_CreateVector(a, c);
		Point3D norm = Point3D::_CrossProduct(v1, v2);
		norm._Normalize();
		return norm;
	}

	void Point3D::_Homogenize() {
		if(w != 0.0) {
			x /= w; y /= w;
			z /= w; w /= w;
		}
	}

	void Point3D::_Normalize() {
		_Divide(
			_Length()
		);
	}

	void Point3D::_Add(const Point3D& vector) {
		x += vector.x; y += vector.y;
		z += vector.z; w += vector.w;
	}

	void Point3D::_Subtract(const Point3D& vector) {
		x -= vector.x; y -= vector.y;
		z -= vector.z; w -= vector.w;
	}

	void Point3D::_Divide(double val) {
		x /= val; y /= val;
		z /= val; w /= val;
	}

	void Point3D::_Multiply(double val) {
		x *= val; y *= val;
		z *= val; w *= val;
	}

	double Point3D::_Length() {
		//return sqrt( x*x + y*y + z*z + w*w );
		return sqrt( x*x + y*y + z*z );
	}

	void Point3D::_ApplyCameraSpaceProjection(Matrix3D *m, int width, int height) {
		// Apply the transformation matrix of triangle
		Point3D result = m->_Multiply(*this); 
		this->x = result.x;
		this->y = result.y;
		this->z = result.z;
		this->w = result.w;

		if(this->w != 0.0) { 

			if(this->w != 1.0) {
				// Homogonize points (Applies perspective projections)
				this->_Homogenize();
			}
	
			// Shift all points so the camera origin is at the center of screen space
			this->_Translate(width/2, height/2, 0.0, 0.0);

		} else {

			// Normalize vectors, e.g. unitize their length
			this->_Normalize();

		}

	}

	void Triangle3D::_ComputeSurfaceNormals(int num_v, Point3D vb[], int num_i, Triangle3D ib[]) {
		for(int n = 0; n < num_i; n++) {
			ib[n].surface_normal = Point3D::_SurfaceNormal(
				vb[ib[n].a], vb[ib[n].b], vb[ib[n].c]
			);
		}
	}

	void Triangle3D::_ComputeVertexNormals(int num_vn, Point3D vn[], int num_v, Point3D vb[], int num_i, Triangle3D ib[]) {
		// Validate Parameters /////////////////////////////////////////
		
		// Vertex normal buffer must be the same size as vertex buffer
		if(num_vn != num_v) return;

		////////////////////////////////////////////////////////////////

		// For each vertex...
		for(int n = 0; n < num_v; n++) {
			// Calculate the average of all surface normals this vertex is a part of...
			double ax = 0.0, ay = 0.0, az = 0.0;
			int count = 0;
			for(int m = 0; m < num_i; m++) {
				Triangle3D *pTriangle = &ib[m];
				// If this vertex is a part of this triangle
				if(pTriangle->a == n || pTriangle->b == n || pTriangle->c == n) {
					// Add it into the average...
					ax += pTriangle->surface_normal.x;
					ay += pTriangle->surface_normal.y;
					az += pTriangle->surface_normal.z;
					// And increase the count...
					count++;
				}
			}
			// If we found at least 1 surface normal...
			if(count > 0) {
				// ...we can complete the average.
				ax /= (double)count;
				ay /= (double)count;
				az /= (double)count;
			}
			// Now the vertex normal is equal to the average of all the
			// surface normals that this vertex is a part of...
			vn[n]._Set(ax, ay, az, 0.0);
		}
		////////////////////////////////////////////////////////////////
	}

	void Light3D::_ApplyToVertex(Mesh3D* pMesh, Triangle3D *pTriangle, const Point3D &pt, const Point3D &lighting_normal, const Point3D &vn, double &r, double &g, double &b, double &a, double &net_i) {
		double i;
		if(lmode & L_SMOOTH) {
			// Smooth Lighting //////////////////////////////////////////////////////////////////////////////////
			Point3D light;
			light.x = vn.x;
			light.y = vn.y;
			light.z = vn.z;

			if(lmode & L_DIRECTIONAL) {
				// Directional Light ////////////////////////////////////////////////////////////////////////////
				// Considers only the direction that the light is going in
				i = this->intensity * Point3D::_DotProduct(this->direction, light);
				// NOTE: The light direction is not yet being transformed

			} else if(lmode & L_POINTLIGHT) {
				// Point Light //////////////////////////////////////////////////////////////////////////////////
				// Considers the direction from the position of the light to the point being lit
				Point3D light_vector = Point3D::_CreateVector(pt, this->position);
				double length = light_vector._Length();
				light_vector._Divide(length);
				i = this->intensity * Point3D::_DotProduct(light_vector, light);
				// NOTE: The light position is not yet being transformed
			}

			if(i < 0.0) i = 0.0;
			if(i > 1.0) i = 1.0;
			// Easing functions can be used on any percentage quantity
			if(lmode & L_FALLOFF1) i = EaseIn(i);
			else if(lmode & L_FALLOFF2) i = EaseOut(i);
			else if(lmode & L_FALLOFF3) i = EaseInOut(i);			
		}
		else if(lmode & L_FACET) {
			// Faceted Lighting /////////////////////////////////////////////////////////////////////////////////
			if(lmode & L_DIRECTIONAL) {
				// Directional Light ////////////////////////////////////////////////////////////////////////////
				double i = this->intensity * Point3D::_DotProduct(this->direction, lighting_normal);
				if(i < 0.0) i = 0.0;
				if(i > 1.0) i = 1.0;
			}
		}
		// Apply the light's intensity and light color to the vertex color
		r = r + i * (this->color.r - r);
		g = g + i * (this->color.g - g);
		b = b + i * (this->color.b - b);
		net_i += i;
	}

	void Light3D::_ApplyToPixel(double alpha, double beta, double gamma, Mesh3D* pMesh, Triangle3D *pTriangle, const Point3D &pt, const Point3D &lighting_normal, const Point3D &v0n, const Point3D &v1n, const Point3D &v2n, double &r, double &g, double &b, double &a) {
		if(lmode & L_SMOOTH) {
			// Smooth Lighting //////////////////////////////////////////////////////////////////////////////////
			Point3D light;
			if(pMesh->rmode & R_BUMPMAP) {
				
				// Bump Mapping ///////////////////////////////////////////
				TextureCoord3D uv0, uv1, uv2;
				double tu, tv;
				int tx, ty;
				uv0 = pMesh->uv[pTriangle->auv];
				uv1 = pMesh->uv[pTriangle->buv];
				uv2 = pMesh->uv[pTriangle->cuv];
				tu = alpha*uv0.tu + beta*uv1.tu + gamma*uv2.tu;
				tv = alpha*uv0.tv + beta*uv1.tv + gamma*uv2.tv;
				tx = tu * pMesh->w2;
				ty = tv * pMesh->h2;

				int pixel = pMesh->pT2[ty*pMesh->w2+tx];

				// Treat color components as a normal quaternion
				_QUATERNION4F q1;
				q1._SetIdentity();
				// (Note: Shift from z=up to z=forward)
				q1.x = -(_COLOR32_ARGB_GET_RED(pixel) - 128.0);
				q1.z = -(_COLOR32_ARGB_GET_GREEN(pixel) - 128.0);
				q1.y = -(_COLOR32_ARGB_GET_BLUE(pixel) - 128.0);
				q1._Normalize();

				// Map the surface normal into a rotation quaternion
				// We need to orient the bump toward the surface normal
				_QUATERNION4F q2;
				q2._SetIdentity();
				q2.x = lighting_normal.x - q1.x;
				q2.y = lighting_normal.y - q2.y;
				q2.z = lighting_normal.z - q2.z;
				q2._Normalize();

				// Apply the space transformation to determine the lighting vector
				//_QUATERNION4F q3 = _QUATERNION4F::_Multiply(q1, q2);

				light.x = q2.x;
				light.y = q2.y;
				light.z = q2.z;
				// Calculate a lighting normal interpolated between the
				// vertex normals of the triangle according to the barycentric
				// coordinates in the triangle of the point being lit...
				//light.x = alpha*v0n.x + beta*v1n.x + gamma*v2n.x;
				//light.y = alpha*v0n.y + beta*v1n.y + gamma*v2n.y;
				//light.z = alpha*v0n.z + beta*v1n.z + gamma*v2n.z;

				// Bump the lighting normal by the bump map vector
				//light.x = (light.x + q3.x)/2.0;
				//light.y = (light.y + q3.y)/2.0;
				//light.z = (light.z + q3.z)/2.0;

			} else {
				
				// Calculate a lighting normal interpolated between the
				// vertex normals of the triangle according to the barycentric
				// coordinates in the triangle of the point being lit...
				light.x = alpha*v0n.x + beta*v1n.x + gamma*v2n.x;
				light.y = alpha*v0n.y + beta*v1n.y + gamma*v2n.y;
				light.z = alpha*v0n.z + beta*v1n.z + gamma*v2n.z;

			}

			double i;

			if(lmode & L_DIRECTIONAL) {

				// Directional Light ////////////////////////////////////////////////////////////////////////////
				// Considers only the direction that the light is going in
				i = this->intensity * Point3D::_DotProduct(this->direction, light);
				// NOTE: The light direction is not yet being transformed

			} else if(lmode & L_POINTLIGHT) {

				// Point Light //////////////////////////////////////////////////////////////////////////////////
				// Considers the direction from the position of the light to the point being lit
				Point3D light_vector = Point3D::_CreateVector(pt, this->position);
				double length = light_vector._Length();
				light_vector._Divide(length);
				i = this->intensity * Point3D::_DotProduct(light_vector, light);
				// NOTE: The light position is not yet being transformed

			}

			if(i < 0.0) i = 0.0;
			if(i > 1.0) i = 1.0;
			// Easing functions can be used on any percentage quantity
			if(lmode & L_FALLOFF1) i = EaseIn(i);
			else if(lmode & L_FALLOFF2) i = EaseOut(i);
			else if(lmode & L_FALLOFF3) i = EaseInOut(i);
			// Apply the light's intensity and light color to the object
			r = r + i * (this->color.r - r);
			g = g + i * (this->color.g - g);
			b = b + i * (this->color.b - b);
		}
		if(lmode & L_FACET) {
			// Faceted Lighting /////////////////////////////////////////////////////////////////////////////////
			if(lmode & L_DIRECTIONAL) {
				// Directional Light ////////////////////////////////////////////////////////////////////////////
				double i = this->intensity * Point3D::_DotProduct(this->direction, lighting_normal);
				if(i < 0.0) i = 0.0;
				if(i > 1.0) i = 1.0;
				r = r + i * (this->color.r - r);
				g = g + i * (this->color.g - g);
				b = b + i * (this->color.b - b);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// _DrawTriangleList : Draws a list of triangles indicated by a Scene object
	void _DrawTriangleList(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene) {
		///////////////////////////////////////////////////////////////////////
		// Validate parameters

		if(pScene == NULL) return;

		//////////////////////////////////////////////////////////////////////
		// Pre-calculate ambient lighting information
		pScene->ambience = 0.0;
		for(int m = 0; m < pScene->num_l; m++) {
			Light3D *pLight = pScene->lights[m];
			if(pLight->lmode & L_AMBIENT) {
				pScene->ambience += pLight->intensity;
			}
		}
		if(pScene->ambience > 1.0) pScene->ambience = 1.0;
		if(pScene->ambience < 0.0) pScene->ambience = 0.0;

		//////////////////////////////////////////////////////////////////////
		// Render each mesh

		for(int n = 0; n < pScene->num_m; n++) {
			Mesh3D *pMesh = pScene->meshes[n];
			_DrawTriangleList(m, video, pZBuffer, width, height, pScene, pMesh);
		}
	}

	// _DrawTriangleList : Draws a list of triangles indicated for the indicated Mesh that is part of a Scene
	void _DrawTriangleList(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene, Mesh3D *pMesh) {
		///////////////////////////////////////////////////////////////////////
		// Validate parameters

		if(video == NULL) return;
		if(pMesh == NULL) return;
		if(pMesh->num_v < 3) return;
		if(pMesh->num_i < 1) return;

		//////////////////////////////////////////////////////////////////////
		// Render each triangle

		for(int n = 0; n < pMesh->num_i; n++) {
			_DrawTriangle(m, video, pZBuffer, width, height, pScene, pMesh, n);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Shirley/Ashikhmin Triangle Rasterization, by Jonathan Nix
	// From page 64 of "Fundamentals of Computer Graphics"
	// by authors Peter Shirley and Michael Ashikhmin"
	//
	// Algorithm:
	//
	//	xmin, xmax, ymin, ymax
	//  for y = ymin to ymax
	//     for x = xmin to xmax
	//        alpha = f12(x,y)/f12(x0,y0)
	//		  beta = f20(x,y)/f20(x1,y1)
	//		  gamma = f01(x,y)/f01(x2,y2)
	//		  if(alpha, beta, gamma each > 0)
	//			 color = alpha*c0 + beta*c1 + gamma*c2
	//			 drawpixel(x, y, color);
	// 
	//   Where: f12, f20, and f01 are defined as:
	//		f12(x,y) = (y1-y2)*x + (x2-x1)*y + x1*y2 - x2*y1
	//		f20(x,y) = (y2-y0)*x + (x0-x2)*y + x2*y0 - x0*y2
	//		f01(x,y) = (y0-y1)*x + (x1-x0)*y + x0*y1 - x1*y0
	//
	#define _f12(xx,yy) ((v1.y-v2.y)*(xx) + (v2.x-v1.x)*(yy) + v1.x*v2.y - v2.x*v1.y)
	#define _f20(xx,yy) ((v2.y-v0.y)*(xx) + (v0.x-v2.x)*(yy) + v2.x*v0.y - v0.x*v2.y)
	#define _f01(xx,yy) ((v0.y-v1.y)*(xx) + (v1.x-v0.x)*(yy) + v0.x*v1.y - v1.x*v0.y)
	#define __min3f(a, b, c) ((a)<(b)?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
	#define __max3f(a, b, c) ((a)>(b)?((a)>(c)?(a):(c)):((b)>(c)?(b):(c)))
	void _DrawTriangle(Matrix3D *m, int *video, double *pZBuffer, int width, int height, Scene3D* pScene, Mesh3D* pMesh, int nTriangleIndex) {

		//////////////////////////////////////////////////////////////////////////////
		// Gather render data

		Color3D c0, c1, c2;										// The color of each vertex
		Color3D lc0, lc1, lc2;										// The light color of each vertex
		double i0, i1, i2;											// The intensity of light on each vertex
		TextureCoord3D uv0, uv1, uv2;									// The texture coordinates of each vertex
		Triangle3D *pTriangle = &pMesh->ib[nTriangleIndex];		// The triangle
		Point3D v0 = pMesh->vb[pTriangle->a];						// Point A of the triangle
		Point3D v1 = pMesh->vb[pTriangle->b];						// Point B of the triangle
		Point3D v2 = pMesh->vb[pTriangle->c];						// Point C of the triangle

		Point3D surface_normal = pTriangle->surface_normal;		// The surface normal of the triangle used for lighting and backface culling

		Point3D v0n = pMesh->vn[pTriangle->a];					// The vertex normals of the triangle
		Point3D v1n = pMesh->vn[pTriangle->b];					// The vertex normals of the triangle
		Point3D v2n = pMesh->vn[pTriangle->c];					// The vertex normals of the triangle

		if(pMesh->rmode & R_COLOR) {
			c0 = pMesh->cb[pMesh->ib[nTriangleIndex].a];
			c1 = pMesh->cb[pMesh->ib[nTriangleIndex].b];
			c2 = pMesh->cb[pMesh->ib[nTriangleIndex].c];
		}

		if(pMesh->rmode & R_TEXTURE) {
			uv0 = pMesh->uv[pMesh->ib[nTriangleIndex].auv];
			uv1 = pMesh->uv[pMesh->ib[nTriangleIndex].buv];
			uv2 = pMesh->uv[pMesh->ib[nTriangleIndex].cuv];
		}

		//////////////////////////////////////////////////////////////////////////////
		// Apply linear space transformation

		if(m != NULL) {
			// Transform the points of the triangle...
			v0._ApplyCameraSpaceProjection(m, width, height);
			v1._ApplyCameraSpaceProjection(m, width, height);
			v2._ApplyCameraSpaceProjection(m, width, height);

			// We also need to transform any normal vectors which are used
			// for lighting and backface culling...
			surface_normal._ApplyCameraSpaceProjection(m, width, height);
			v0n._ApplyCameraSpaceProjection(m, width, height);
			v1n._ApplyCameraSpaceProjection(m, width, height);
			v2n._ApplyCameraSpaceProjection(m, width, height);

			// Clip any triangles that are behind the viewer
			if(v0.z > 0.0 && v1.z > 0.0 && v2.z > 0.0) return;
		}

		//////////////////////////////////////////////////////////////////////////////
		// Calculate the bounding rectangle of the triangle in screen space

		int xmin = (int)__min3f(v0.x, v1.x, v2.x);
		int ymin = (int)__min3f(v0.y, v1.y, v2.y);
		int xmax = (int)__max3f(v0.x, v1.x, v2.x);
		int ymax = (int)__max3f(v0.y, v1.y, v2.y);

		// Clip any region greater than 10 pixels in size
		if(xmax - xmin > 10) return;
		if(ymax - ymin > 10) return;

		//////////////////////////////////////////////////////////////////////////////
		// Detect if triangle is entirely off screen

		if(xmax < 0) return;
		if(ymax < 0) return;
		if(xmin > width-1) return;
		if(ymin > height-1) return;

		//////////////////////////////////////////////////////////////////////////////
		// Clip the bounding rectangle to the viewport

		if(xmin < 0) xmin = 0;
		if(ymin < 0) ymin = 0;
		if(xmax > width-1) xmax = width-1;
		if(ymax > height-1) ymax = height-1;

		//////////////////////////////////////////////////////////////////////////////
		// Pre-calculate Gouraud Shading (lighting information on vertices)

		if(pMesh->rmode & R_GOURAUD) {
			
			// Clear out lighting information ////////////////////////////////////////
			lc0.r = lc0.g = lc0.b = lc0.a = 0.0;
			lc1.r = lc1.g = lc1.b = lc1.a = 0.0;
			lc2.r = lc2.g = lc2.b = lc2.a = 0.0;
			i0 = i1 = i2 = 0.0;
			
			// Apply each light to each vertex ///////////////////////////////////////
			if(pScene != NULL && pScene->lights != NULL) {
				for(int m = 0; m < pScene->num_l; m++) {
					Light3D *pLight = pScene->lights[m];

					pLight->_ApplyToVertex(pMesh, pTriangle, v0, surface_normal, v0n, lc0.r, lc0.g, lc0.b, lc0.a, i0);
					pLight->_ApplyToVertex(pMesh, pTriangle, v1, surface_normal, v1n, lc1.r, lc1.g, lc1.b, lc1.a, i1);
					pLight->_ApplyToVertex(pMesh, pTriangle, v2, surface_normal, v2n, lc2.r, lc2.g, lc2.b, lc2.a, i2);

				}
			}

			// Validate the net intensity
			if(i0 < 0.0) i0 = 0.0; else if(i0 > 1.0) i0 = 1.0;
			if(i1 < 0.0) i1 = 0.0; else if(i1 > 1.0) i1 = 1.0;
			if(i2 < 0.0) i2 = 0.0; else if(i2 > 1.0) i2 = 1.0;

		}

		//////////////////////////////////////////////////////////////////////////////
		// Now for the main algorithm

		int pixel;
		double alpha, beta, gamma;
		double r, g, b, a;
		double tu, tv;
		int tx, ty;
		for(int y = ymin; y <= ymax; y++) {
			for(int x = xmin; x <= xmax; x++) {
				alpha = _f12(x,y)/_f12(v0.x,v0.y);
				beta = _f20(x,y)/_f20(v1.x,v1.y);
				gamma = _f01(x,y)/_f01(v2.x,v2.y);
				if(alpha>=0 && beta>=0 && gamma>=0) {

					double z = alpha*v0.z + beta*v1.z + gamma*v2.z;

					// Clip anything not in camera space /////////////////////////////
					if(z > 0.0) continue;

					// Calculate Z buffer value //////////////////////////////////////

					if(pMesh->rmode & R_ZBUFFER) {
						double zb = pZBuffer[y*width+x];

						// If the z we're drawing (pointing down the negative z axis)
						// is farther away than the point already there, we don't need
						// to place this pixel.
						if(z < zb) continue;

						// Otherwise, place this value in the Z-Buffer so the next time
						// someone draws a pixel here they can see if they're farther
						// away than what was already drawn here.
						pZBuffer[y*width+x] = z;
					}

					// Calculate Color of Pixel //////////////////////////////////////
					if(pMesh->rmode & R_COLOR) {
						r = alpha*c0.r + beta*c1.r + gamma*c2.r;
						g = alpha*c0.g + beta*c1.g + gamma*c2.g;
						b = alpha*c0.b + beta*c1.b + gamma*c2.b;
						a = 255;
					}
					if(pMesh->rmode & R_TEXTURE) {
						tu = alpha*uv0.tu + beta*uv1.tu + gamma*uv2.tu;
						tv = alpha*uv0.tv + beta*uv1.tv + gamma*uv2.tv;

						tx = tu * pMesh->w1;
						ty = tv * pMesh->h1;

						pixel = pMesh->pT1[ty*pMesh->w1+tx];

						// Extract color components so they can be processed through lighting.
						// NOTE: If the texture was proprocessed with a double color channel on range [0,1]
						// it would result in a performance improvement.
						r = _COLOR32_ARGB_GET_RED(pixel);
						g = _COLOR32_ARGB_GET_GREEN(pixel);
						b = _COLOR32_ARGB_GET_BLUE(pixel);
						a = _COLOR32_ARGB_GET_ALPHA(pixel);
					}
					///////////////////////////////////////////////////////////////////
					// Lighting....

					// Determine the position in camera space being lit ///////////////
					Point3D &pt = Point3D::_Create((double)x, (double)y, z, 1.0);
					
					// Apply Ambience /////////////////////////////////////////////////
					r *= pScene->ambience;
					g *= pScene->ambience;
					b *= pScene->ambience;

					// Apply each light ///////////////////////////////////////////////

					if(pMesh->rmode & R_PHONG) {

						// Apply per-pixel lighting to each pixel...
						if(pScene != NULL && pScene->lights != NULL) {
							for(int m = 0; m < pScene->num_l; m++) {
								Light3D *pLight = pScene->lights[m];
								pLight->_ApplyToPixel(alpha, beta, gamma, pMesh, pTriangle, pt, surface_normal, v0n, v1n, v2n, r, g, b, a);
							}
						}

					} else if(pMesh->rmode & R_GOURAUD) {

						// Apply per-vertex lighting to each pixel, by interpolating
						// from the current color of the pixel toward the light color
						// of the pixel based on the interpolated light intensity.
						double i = alpha*i0 + beta*i1 + gamma*i2;
						r = r + i * ((alpha*lc0.r + beta*lc1.r + gamma*lc2.r) - r);
						g = g + i * ((alpha*lc0.g + beta*lc1.g + gamma*lc2.g) - g);
						b = b + i * ((alpha*lc0.b + beta*lc1.b + gamma*lc2.b) - b);

					}
					
					///////////////////////////////////////////////////////////////////
					// Determine pixel value from color components

					pixel = _COLOR32_ARGB(a,r,g,b);

					///////////////////////////////////////////////////////////////////
					// Render the pixel to the screen

					_PUTPIXEL(video, (int)x, (int)y, width, height, pixel);
				}
			}
		}
	}

	void _ClearZBuffer(double *pZBuffer, int nWidth, int nHeight) {
		if(pZBuffer == NULL) return;
		int n = nWidth*nHeight;
		do {
			*pZBuffer = -10000.0;
			pZBuffer++;
		} while(--n > 0);
	}

}

