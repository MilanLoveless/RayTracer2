// OBJImporter.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OBJImporter.h"

namespace ThreeD
{
	_MESH* _OBJIMPORTER::_ImportMesh(char *filename)
	{
		_MESH* mesh = new _MESH();
		FILE *obj_file;
		char* scan_in;
		bool end_file = false;
		obj_file = fopen(filename, "r");
		if(obj_file != NULL)
		{
			while(!feof(obj_file))
			{
				fscanf(obj_file, "%s", scan_in);

				// Scan in Vertices
				while(strcmp(scan_in, "v") == 0)
				{
					_DOUBLE vx, vy, vz;
					fscanf(obj_file, "%f %f %f", &vx, &vy, &vz);
					mesh->vertex_buffer.push_back(_VERTEX4F(vx, vy, vz, 1.0));
					fscanf(obj_file, "%s", scan_in);
				}
				// Scan in Normals
				while(strcmp(scan_in, "vn") == 0)
				{
					_DOUBLE nx, ny, nz;
					fscanf(obj_file, "%f %f %f", &nx, &ny, &nz);
					mesh->normal_buffer.push_back(_VERTEX4F(nx, ny, nz, 0.0));
					fscanf(obj_file, "%s", scan_in);
				}
				// Scan in UVs
				while(strcmp(scan_in, "vt") == 0)
				{
					_DOUBLE tx, ty, trashz;
					fscanf(obj_file, "%f %f %f", &tx, &ty, &trashz);
					mesh->uv_buffer.push_back(_POINT2D(tx, ty));
					fscanf(obj_file, "%s", scan_in);
				}

				// Scan in Triangle Indices
				while(strcmp(scan_in, "f") == 0)
				{
					_MESHTRIANGLE *triangle = new _MESHTRIANGLE();
					int v0, v1, v2, n0, n1, n2, t0, t1, t2;
					fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d", &v0, &n0, &t0, &v1, &n1, &t1, &v2, &n2, &t2);
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
					// Push Back Triangle
					triangle->_CalculateNormal(false);
					mesh->triangle_buffer.push_back(*triangle);
					fscanf(obj_file, "%s", scan_in);
				}
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