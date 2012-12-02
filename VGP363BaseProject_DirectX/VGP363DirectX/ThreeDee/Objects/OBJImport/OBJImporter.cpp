// OBJImporter.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>

#include "OBJImporter.h"

namespace ThreeD
{
	_MESH* _OBJIMPORTER::_ImportMesh(char *filename)
	{
		_MESH* mesh = new _MESH();
		FILE *obj_file;
		char *scan_in = new char[50];
		bool end_file = false;
		obj_file = fopen(filename, "r");
		int countbi = 0;
		int counttan = 0;
		int foo;
		if(obj_file != NULL)
		{
			
			foo = fscanf(obj_file, "%s", scan_in);

			// Garbage
			while(strcmp(scan_in, "v") != 0)
			{
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Scan in Vertices
			while(strcmp(scan_in, "v") == 0)
			{
				_DOUBLE vx, vy, vz;
				foo = fscanf(obj_file, "%f %f %f", &vx, &vy, &vz);
				mesh->vertex_buffer.push_back(_VERTEX4F(vx * -1.0, vy, vz, 1.0));
				foo = fscanf(obj_file, "%s", scan_in);
			}
				
			// Garbage
			while(strcmp(scan_in, "vn") != 0)
			{
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Scan in Normals
			while(strcmp(scan_in, "vn") == 0)
			{
				_DOUBLE nx, ny, nz;
				foo = fscanf(obj_file, "%f %f %f", &nx, &ny, &nz);
				mesh->normal_buffer.push_back(_VERTEX4F(nx * -1.0, ny, nz, 0.0));
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Garbage
			while(strcmp(scan_in, "vt") != 0)
			{
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Scan in UVs
			while(strcmp(scan_in, "vt") == 0)
			{
				_DOUBLE tx, ty, trashz;
				foo = fscanf(obj_file, "%f %f %f", &tx, &ty, &trashz);
				mesh->uv_buffer.push_back(_POINT2D(tx, ty));
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Garbage
			while(strcmp(scan_in, "f") != 0)
			{
				foo = fscanf(obj_file, "%s", scan_in);
			}

			// Scan in Triangle Indices
			while(strcmp(scan_in, "f") == 0)
			{
				_MESHTRIANGLE *triangle = new _MESHTRIANGLE();
				int v0, v1, v2, n0, n1, n2, t0, t1, t2;
				foo = fscanf(obj_file, "%d / %d / %d %d / %d / %d %d / %d / %d", &v0, &t0, &n0, &v1, &t1, &n1, &v2, &t2, &n2);
				// Assign Vertex Indices
				triangle->p0 = v0 - 1;
				triangle->p1 = v1 - 1;
				triangle->p2 = v2 - 1;
				// Assign Normal Indices 
				triangle->n0 = n0 - 1;
				triangle->n1 = n1 - 1;
				triangle->n2 = n2 - 1;
				// Assign Texture Indices
				triangle->uv0 = t0 - 1;
				triangle->uv1 = t1 - 1;
				triangle->uv2 = t2 - 1;
				// Calculate Binormal and Tangent
				
				// Push Back Triangle
				triangle->mesh_ptr = mesh;
				triangle->_CalculateNormal(false);
				triangle->_CalculateTS();
				triangle->_CalculateArea();
				mesh->triangle_buffer.push_back(*triangle);
				foo = fscanf(obj_file, "%s", scan_in);
			}
			fclose(obj_file);
		}
		mesh->n_vertices = mesh->vertex_buffer.size();
		mesh->n_uvs = mesh->uv_buffer.size();
		mesh->n_triangles = mesh->triangle_buffer.size();
		//mesh->_SetBBox();
		return mesh;
	}
}