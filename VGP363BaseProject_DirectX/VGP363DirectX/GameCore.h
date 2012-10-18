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
#include "CORE\CORE.Animation.h"
#include "CORE\CORE.Collection.h"
#include "CORE\CORE.Collision.h"
#include "CORE\CORE.Controller.h"
#include "CORE\CORE.Math.h"

#include "CORE\CORE.Hardware.3D.h"
#include "CORE\CORE.Hardware.Drawing.3D.h"
#include "CORE\CORE.Hardware.3D.Texture.h"

#include "CORE\CORE.Drawing.h"
#include "CORE\3D\CORE.Drawing.Primitives.h"
#include "CORE\3D\CORE.Matrix.h"
#include "CORE\3D\CORE.Quaternion.h"

namespace GAMECORE {

	// Application module
	class MainApp {
	public:
		static void _OnInitialize();
		static void _OnUninitialize();
		static void _OnFrame();
	};

} // end namespace

//#endif