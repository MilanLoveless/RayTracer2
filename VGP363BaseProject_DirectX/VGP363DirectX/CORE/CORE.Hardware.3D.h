// CORE.Hardware.3D.h
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_HARDWARE_3D_
#define __CORE_HARDWARE_3D_

//#include "..\GameCore.h"

namespace CORE {
	namespace HARDWARE {

		extern IDirect3D9* g_pDirect3D;
		extern IDirect3DDevice9* g_pD3DDevice;
		extern IDirect3DSurface9* g_pBackSurface;
		extern D3DCAPS9 g_D3DDeviceCaps;
		extern D3DPRESENT_PARAMETERS g_D3DPresentMode;

		int _InitializeDirect3D(int resWidth, int resHeight, D3DFORMAT resFormat, HWND hWnd, BOOL bWindowedMode = false);
		int _UninitializeDirect3D();

		int _ClearBackBuffer();
		int _DisplayBackBuffer();
		int _BeginDrawing ();
		int _EndDrawing ();

	} // End namespace HARDWARE
} // End namespace CORE

#endif