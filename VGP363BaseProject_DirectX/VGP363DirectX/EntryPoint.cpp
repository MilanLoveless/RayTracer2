// EntryPoint.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCore.h"

HINSTANCE g_hInstance;
HWND g_hMainWnd;
BOOL g_bAppRunning;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
int _OnInitInstance(HINSTANCE hInstance);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
    g_bAppRunning = true;

	_OnInitInstance(hInstance);

	// CALL INITIALIZATION FUNCTIONS HERE
	CORE::HARDWARE::_InitializeDirect3D(0, 0, D3DFMT_A8R8G8B8, g_hMainWnd, true);
	CORE::HARDWARE::_InitializeCOREDrawing3D(0, 0, 800, 600);
	GAMECORE::MainApp::_OnInitialize();

    MSG msg;
    while(g_bAppRunning)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		// CALL PER FRAME FUNCTIONS HERE (for now)
		GAMECORE::MainApp::_OnFrame();
    }

	// CALL UNINITIALIZATION FUNCTIONS HERE
	GAMECORE::MainApp::_OnUninitialize();
	CORE::HARDWARE::_UninitializeCOREDrawing3D();
	CORE::HARDWARE::_UninitializeDirect3D();

    return 0;
}

LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
    {

		// ADD CUSTOM WINDOWS MESSAGE HANDLERS HERE

	case WM_DESTROY:
        g_bAppRunning = false;
        break;
    }

    return DefWindowProc(hWnd,uMessage,wParam,lParam);
}

int _OnInitInstance(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = _WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "_GameCore_WndClass_";
    wc.hIconSm = NULL; ///LoadIcon (hInstance, MAKEINTRESOURCE(IDI_GAMECORE_ICON));

    if(!RegisterClassEx(&wc)) {
        return false;
	}

    g_hMainWnd = CreateWindowEx(NULL, "_GameCore_WndClass_", "VGP363 Ray Trace Renderer (DirectX)",
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU, 0, 0, 800, 600,
        NULL, NULL, hInstance, NULL
	);

    if(!g_hMainWnd) {
        return false;
	}

	RECT rect;
	GetWindowRect(g_hMainWnd, &rect);
	int nFullWidth = rect.right - rect.left;
	int nFullHeight = rect.bottom - rect.top;
	
	SetWindowPos(
		g_hMainWnd, NULL,
		GetSystemMetrics(SM_CXSCREEN)/2 - nFullWidth/2,
		GetSystemMetrics(SM_CYSCREEN)/2 - nFullHeight/2,
		nFullWidth, nFullHeight, SWP_SHOWWINDOW
	);

    return true;
}
