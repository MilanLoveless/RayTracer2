// OBJImporter.h
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string.h>
#include "../Mesh.h"
#include "../MeshTriangle.h"

namespace ThreeD
{
	class _OBJIMPORTER
	{
	public:
		static _MESH* _ImportMesh(char *filename);
		static void _CalculateTS(_MESH &mesh, _MESHTRIANGLE &tri, int &ibi, int &itan);
	};
}