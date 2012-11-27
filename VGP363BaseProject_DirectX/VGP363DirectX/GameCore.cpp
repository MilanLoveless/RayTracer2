// GameCore.cpp
////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCore.h"

namespace GAMECORE {

	ThreeD::_WORLD *world3D = NULL;
	ThreeD::_CAMERA *camera = NULL;

	CORE::HARDWARE::TEXTUREINFO *g_pBackBuffer;

	int *g_pRenderBuffer = NULL;
	int _W = 800;
	int _H = 600;

	void MainApp::_OnInitialize() {
		_SeedRand;
		g_pBackBuffer = CORE::HARDWARE::_CreateTexture(0, 800, 600);
		// Initialize any other resources for the application here
		world3D = new ThreeD::_WORLD();
		camera = new ThreeD::_PINHOLE(world3D);
		ThreeD::_GEOMETRICOBJECT *meshThing = ThreeD::_OBJIMPORTER::_ImportMesh("./OBJFiles/leatherjacket.txt");
		CORE::HARDWARE::TEXTUREINFO *normalmap = CORE::HARDWARE::_LoadTexture(1, "./ImageFiles/LeatherJacket_N.png", 2048, 2048);
		CORE::HARDWARE::TEXTUREINFO *diffusemap = CORE::HARDWARE::_LoadTexture(2, "./ImageFiles/crate_d.tga", 1024, 1024);
		CORE::HARDWARE::TEXTUREINFO *specularmap = CORE::HARDWARE::_LoadTexture(3, "./ImageFiles/crate_s.tga", 1024, 1024);
		ThreeD::_MAPPEDPHONG *phong = new ThreeD::_MAPPEDPHONG();
		phong->_SetNormal(normalmap);
		phong->_SetDiffuse(diffusemap);
		phong->_SetSpecular(specularmap);
		meshThing->material_ptr = phong;
		world3D->_AddObject(meshThing);
		world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(-1000.0, 1000.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 1.0, 1.0, 1.0), 1.0));
		//world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(500.0, -600.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 0.1, 0.1, 1.0), 1.0));
		//world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(0.0, 0.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 0.1, 1.0, 0.1), 1.0));
		//world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(0.0, 0.0, 1500.0, 1.0), 500.0));
		//world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(-700.0, 500.0, 2500.0, 1.0), 700.0));
		//world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(-300.0, 300.0, 800.0, 1.0), 100.0));
		//world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(300.0, 300.0, 800.0, 1.0), 300.0));
	}

	void MainApp::_OnUninitialize() {
		CORE::HARDWARE::_UnloadTexture(&g_pBackBuffer);
		// Unload any other resources for the application here
	}

	void MainApp::_OnRenderFrame() {

		if(g_pRenderBuffer != NULL) {

			int *video = g_pRenderBuffer;
			int w = _W;
			int h = _H;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			// Render the scene
			camera->_RenderScene(video, *world3D);
			////////////////////////////////////////////////////////////////////////////////////////////////////

		}

	}

	void MainApp::_OnDisplayFrame() {
		CORE::HARDWARE::_ClearBackBuffer();
		CORE::HARDWARE::_BeginDrawing();

		CORE::HARDWARE::_LockTexture(g_pBackBuffer);

		if(g_pRenderBuffer == NULL) {
			_W = g_pBackBuffer->_nActualWidth;
			_H = g_pBackBuffer->_nHeight;
			g_pRenderBuffer = new int[_W*_H];

			for(int y = 0; y < _H; y++) {
				for(int x = 0; x < _W; x++) {
					g_pRenderBuffer[y*_W+x] = 0xFF000000;
				}
			}
		}

		for(int n = 0; n < _W*_H; n++) {
			g_pBackBuffer->_video[n] = g_pRenderBuffer[n];
		}

		CORE::HARDWARE::_UnlockTexture(g_pBackBuffer);

		CORE::HARDWARE::_FlipSurface(g_pBackBuffer->_pSurface);

		CORE::HARDWARE::_EndDrawing();
		CORE::HARDWARE::_DisplayBackBuffer();
	}

} // End namespace