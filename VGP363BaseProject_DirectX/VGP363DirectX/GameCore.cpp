// GameCore.cpp
////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCore.h"

namespace GAMECORE {
	
	ThreeD::_WORLD world3d;
	_3DSPHERE *scene_ptr;

	CORE::HARDWARE::TEXTUREINFO *g_pBackBuffer;
	float *g_pZBuffer = NULL;

	void MainApp::_OnInitialize() {
		g_pBackBuffer = CORE::HARDWARE::_CreateTexture(0, SCREENWIDTH, SCREENHEIGHT);
		scene_ptr = new _3DSPHERE(&world3d);
		scene_ptr->_Initialize();
		scene_ptr->camera._Initialize(SCREENWIDTH, SCREENHEIGHT, 60);

		// Initialize any other resources for the application here
	}

	void MainApp::_OnUninitialize() {
		CORE::HARDWARE::_UnloadTexture(&g_pBackBuffer);
		// Unload any other resources for the application here
	}

	void MainApp::_OnFrame() {
		CORE::HARDWARE::_ClearBackBuffer();
		CORE::HARDWARE::_BeginDrawing();

		CORE::HARDWARE::_LockTexture(g_pBackBuffer);

		int *video = g_pBackBuffer->_video;
		int w = g_pBackBuffer->_nActualWidth;
		int h = g_pBackBuffer->_nHeight;

		// Clear screen
		for(int y = 0; y < h; y++) {
			for(int x = 0; x < w; x++) {
				video[y*w+x] = 0xFFF1F1F1;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		// Render the scene

		scene_ptr->_Draw(g_pBackBuffer->_video, SCREENWIDTH, SCREENHEIGHT);

		// Put your core rendering code here

		////////////////////////////////////////////////////////////////////////////////////////////////////

		CORE::HARDWARE::_UnlockTexture(g_pBackBuffer);

		CORE::HARDWARE::_FlipSurface(g_pBackBuffer->_pSurface);

		CORE::HARDWARE::_EndDrawing();
		CORE::HARDWARE::_DisplayBackBuffer();
	}

} // End namespace