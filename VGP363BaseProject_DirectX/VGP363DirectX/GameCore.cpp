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
		ThreeD::_GEOMETRICOBJECT *meshThing = ThreeD::_OBJIMPORTER::_ImportMesh("./OBJFiles/crate.txt");
		CORE::HARDWARE::TEXTUREINFO *normalmap = CORE::HARDWARE::_LoadTexture(1, "./ImageFiles/crate_n.tga", 1024, 1024);
		CORE::HARDWARE::TEXTUREINFO *diffusemap = CORE::HARDWARE::_LoadTexture(2, "./ImageFiles/crate_d.tga", 1024, 1024);
		CORE::HARDWARE::TEXTUREINFO *specularmap = CORE::HARDWARE::_LoadTexture(3, "./ImageFiles/crate_s.tga", 1024, 1024);
		ThreeD::_MAPPEDPHONG *phong = new ThreeD::_MAPPEDPHONG();
		phong->_SetNormal(normalmap);
		phong->_SetDiffuse(diffusemap);
		phong->_SetSpecular(specularmap);
		meshThing->material_ptr = phong;
		world3D->_AddObject(meshThing);
		world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(-5000.0, 5000.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 1.0, 1.0, 1.0), 1.0));
		//world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(500.0, -600.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 0.1, 0.1, 1.0), 1.0));
		//world3D->_AddLight(new ThreeD::_POINTLIGHT(ThreeD::_VERTEX4F(0.0, 0.0, 0.0, 1.0), ThreeD::_COLOR4F(1.0, 0.1, 1.0, 0.1), 1.0));
		/*world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(0.0, 0.0, 3500.0, 1.0), 500.0));
		world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(-700.0, 500.0, 3500.0, 1.0), 700.0));
		world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(-300.0, 300.0, 1800.0, 1.0), 100.0));
		world3D->_AddObject(new ThreeD::_SPHERE(ThreeD::_VERTEX4F(300.0, 300.0, 1800.0, 1.0), 300.0));*/
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

		int w = g_pBackBuffer->_nActualWidth;
		int h = g_pBackBuffer->_nHeight;

		if(g_pRenderBuffer != NULL) {
			for(int y = 0; y < h; y++) {
				for(int x = 0; x < w; x++) {
					if(x < _W && y < _H) {
						g_pBackBuffer->_video[y*w+x] = g_pRenderBuffer[y*_W+x];
					}
				}
			}
		}

		CORE::HARDWARE::_UnlockTexture(g_pBackBuffer);

		CORE::HARDWARE::_FlipSurface(g_pBackBuffer->_pSurface);

		CORE::HARDWARE::_EndDrawing();
		CORE::HARDWARE::_DisplayBackBuffer();
	}

} // End namespace