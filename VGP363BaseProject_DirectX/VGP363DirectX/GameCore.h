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

#include "CORE\CORE.Drawing.h"
//#include "CORE\3D\CORE.Drawing.Primitives.h"
//#include "CORE\3D\CORE.Matrix.h"
//#include "CORE\3D\CORE.Quaternion.h"

#include "Scenes\Scene.h"
#include "Scenes\SphereScene.h"

#include "ThreeDee\Cameras\RayCamera.h"

#include "ThreeDee\Components\Color.h"
#include "ThreeDee\Components\Constants.h"
#include "ThreeDee\Components\Matrix.h"
#include "ThreeDee\Components\Mesh.h"
#include "ThreeDee\Components\Vertex.h"

#include "ThreeDee\Lights\Light.h"

#include "ThreeDee\Objects\GenericObject.h"
#include "ThreeDee\Objects\SphereObject.h"

#include "ThreeDee\RayTracer\Tracers\RayTracer.h"

#include "ThreeDee\World\World.h"



#define SCREENWIDTH 800
#define SCREENHEIGHT 600

namespace GAMECORE {

	extern ThreeD::_WORLD world3d;
	extern _3DSPHERE *scene_ptr;

	// Application module
	class MainApp {
	public:
		static void _OnInitialize();
		static void _OnUninitialize();
		static void _OnFrame();
	};

} // end namespace

//#endif