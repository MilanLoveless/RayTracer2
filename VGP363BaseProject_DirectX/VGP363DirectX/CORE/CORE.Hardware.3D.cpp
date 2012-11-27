// CORE.Hardware.3D.cpp
/////////////////////////////////////////////////////////////////////////////////////////

#include "CORE.Hardware.3D.h"

namespace CORE {
	namespace HARDWARE {

		IDirect3D9* g_pDirect3D;
		IDirect3DDevice9* g_pD3DDevice;
		IDirect3DSurface9* g_pBackSurface;
		D3DCAPS9 g_D3DDeviceCaps;
		D3DPRESENT_PARAMETERS g_D3DPresentMode;

		int _InitializeDirect3D(int nWidth, int nHeight, D3DFORMAT format, HWND hWnd, BOOL bWindowedMode)
		{
			HRESULT hr;

			g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

			if (g_pDirect3D == NULL) {
				return FALSE;
			}

			ZeroMemory(&g_D3DDeviceCaps, sizeof(g_D3DDeviceCaps));
			if(FAILED(g_pDirect3D->GetDeviceCaps (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &g_D3DDeviceCaps))) {
				return FALSE;
			}

			ZeroMemory(&g_D3DPresentMode, sizeof(g_D3DPresentMode));
			g_D3DPresentMode.SwapEffect = D3DSWAPEFFECT_FLIP;
			g_D3DPresentMode.hDeviceWindow = hWnd;
			g_D3DPresentMode.BackBufferCount = 1;

			if(bWindowedMode)
			{
				D3DDISPLAYMODE d3ddm;
				RECT rectWindow;

				g_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
				GetClientRect(hWnd, &rectWindow);

				nWidth = rectWindow.right - rectWindow.left;
				nHeight = rectWindow.bottom - rectWindow.top;

				g_D3DPresentMode.Windowed = true;
				g_D3DPresentMode.BackBufferWidth = nWidth;
				g_D3DPresentMode.BackBufferHeight = nHeight;
				g_D3DPresentMode.BackBufferFormat = d3ddm.Format;
			}
			else
			{        
				g_D3DPresentMode.Windowed = false;
				g_D3DPresentMode.BackBufferWidth = nWidth;
				g_D3DPresentMode.BackBufferHeight = nHeight;
				g_D3DPresentMode.BackBufferFormat = format;
			}

			if (g_D3DDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			{    
				hr = g_pDirect3D->CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
					D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_D3DPresentMode, &g_pD3DDevice
				);
			}
			else
			{
				hr = g_pDirect3D->CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPresentMode, &g_pD3DDevice
				);
			}

			if(FAILED(hr)) {
				return FALSE;
			}

			// Get back buffer /////////////////////////////////////////////////////////////
			g_pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackSurface);

			return TRUE;
		}

		int _UninitializeDirect3D()
		{
			if (g_pD3DDevice) {
				g_pD3DDevice->Release();
			}

			if (g_pDirect3D) {
				g_pDirect3D->Release();
			}

			return TRUE;
		}

		int _ClearBackBuffer() { 
			return g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, 0.0f, 0); 
		}

		int _DisplayBackBuffer() { 
			return g_pD3DDevice->Present(NULL, NULL, NULL, NULL); 
		}

		int _BeginDrawing() { 
			return g_pD3DDevice->BeginScene(); 
		}

		int _EndDrawing() { 
			return g_pD3DDevice->EndScene(); 
		}

	} // End namespace HARDWARE
} // End namespace CORE