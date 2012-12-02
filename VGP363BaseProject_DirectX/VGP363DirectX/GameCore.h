// GameCore.h
//////////////////////////////////////////////////////////////

#pragma once
//#ifndef __GAMECORE_H_
//#define __GAMECORE_H_

#include <Windows.h>
#include <dxerr.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <MMSYSTEM.h>
#include <dsound.h>

#include <stdio.h>

// Include all of your further H files here
//#include "CORE\CORE.Animation.h"
//#include "CORE\CORE.Collection.h"
//#include "CORE\CORE.Collision.h"
//#include "CORE\CORE.Controller.h"
//#include "CORE\CORE.Math.h"

#include "CORE\CORE.Hardware.3D.h"
#include "CORE\CORE.Hardware.Drawing.3D.h"
#include "CORE\CORE.Hardware.3D.Texture.h"

//#include "CORE\CORE.Drawing.h"
//#include "CORE\3D\CORE.Drawing.Primitives.h"
//#include "CORE\3D\CORE.Matrix.h"
//#include "CORE\3D\CORE.Quaternion.h"

#include "ThreeDee\World\World.h"
#include "ThreeDee\Cameras\Pinhole.h"
#include "ThreeDee\Cameras\Orthographic.h"
#include "ThreeDee\RayTracer\Tracers\Whitted.h"
#include "ThreeDee\Objects\SphereObject.h"
#include "ThreeDee\RayTracer\Materials\Matte.h"
#include "ThreeDee\RayTracer\Lights\Ambient.h"
#include "ThreeDee\RayTracer\Lights\PointLight.h"
#include "ThreeDee\Components\Constants.h"
#include "ThreeDee\Objects\OBJImport\OBJImporter.h"
#include "ThreeDee\Objects\Mesh.h"
#include "ThreeDee\RayTracer\Materials\IridescentPhong.h"
#include "ThreeDee\RayTracer\Materials\MappedPhong.h"
#include "ThreeDee\RayTracer\Lights\AmbientOccluder.h"

namespace GAMECORE {

	// Application module
	class MainApp {
	public:
		static void _OnInitialize();
		static void _OnUninitialize();
		static void _OnRenderFrame();
		static void _OnDisplayFrame();
	};

	extern int _W, _H;
	extern int *g_pRenderBuffer;
	extern ThreeD::_CAMERA *camera;
	extern ThreeD::_WORLD *world3D;
} // end namespace

//#endif