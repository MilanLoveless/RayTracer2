// OBJImporter.h
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string.h>
#include "../Mesh.h"

namespace ThreeD
{
	class _OBJIMPORTER
	{
	public:
		static _MESH* _ImportMesh(char *filename);
	};
}