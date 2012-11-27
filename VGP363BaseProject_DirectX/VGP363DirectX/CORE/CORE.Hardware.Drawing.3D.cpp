// CORE.Hardware.Drawing.3D.cpp
///////////////////////////////////////////////////////////////////////////////////

#include "CORE.Hardware.Drawing.3D.h"

namespace CORE {
	namespace HARDWARE {

		const DWORD _2D_VERTEX_OPTIONS = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
		IDirect3DVertexBuffer9* g_pVertexBuffer;

		struct _2D_VERTEX
		{
			float x;
			float y;
			float z;
			float rhw;
			D3DCOLOR color;
			float u;
			float v;
		};

		void _2D_RenderVertices(RECT *pRect) {
			const int WHITE = 0xFFFFFFFF;
			_2D_VERTEX* pVertices;
			g_pVertexBuffer->Lock(0, 0, (void **)&pVertices, NULL);
			pVertices[0].color = WHITE;
			pVertices[0].x = (float)pRect->left - 0.5f;
			pVertices[0].y = (float)pRect->top - 0.5f;
			pVertices[0].z = 0.0f;
			pVertices[0].rhw = 1.0f;
			pVertices[0].u = 0.0f;
			pVertices[0].v = 0.0f;
			pVertices[1].color = WHITE;
			pVertices[1].x = (float)pRect->right - 0.5f;
			pVertices[1].y = (float)pRect->top - 0.5f;
			pVertices[1].z = 0.0f;
			pVertices[1].rhw = 1.0f;
			pVertices[1].u = 1.0f;
			pVertices[1].v = 0.0f;
			pVertices[2].color = WHITE;
			pVertices[2].x = (float)pRect->right - 0.5f;
			pVertices[2].y = (float)pRect->bottom - 0.5f;
			pVertices[2].z = 0.0f;
			pVertices[2].rhw = 1.0f;
			pVertices[2].u = 1.0f;
			pVertices[2].v = 1.0f;
			pVertices[3].color = WHITE;
			pVertices[3].x = (float)pRect->left - 0.5f;
			pVertices[3].y = (float)pRect->bottom - 0.5f;
			pVertices[3].z = 0.0f;
			pVertices[3].rhw = 1.0f;
			pVertices[3].u = 0.0f;
			pVertices[3].v = 1.0f;
			g_pVertexBuffer->Unlock();
		}

		void _2D_SetRenderSettings() {
			g_pD3DDevice->SetVertexShader(NULL);
			g_pD3DDevice->SetFVF(_2D_VERTEX_OPTIONS);

			g_pD3DDevice->SetStreamSource(
				0, g_pVertexBuffer, 0, sizeof(_2D_VERTEX)
			);

			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		}

		void _InitializeCOREDrawing3D(int left, int top, int right, int bottom) {
			RECT rect;
			rect.left = left;
			rect.top = top;
			rect.right = right;
			rect.bottom = bottom;
			g_pD3DDevice->CreateVertexBuffer(
				sizeof(_2D_VERTEX) * 4, NULL, _2D_VERTEX_OPTIONS, D3DPOOL_MANAGED,
				&g_pVertexBuffer, NULL
			);

			_2D_RenderVertices(&rect);

			_2D_SetRenderSettings();
		}

		void _UninitializeCOREDrawing3D() {
			if (g_pVertexBuffer) {
				g_pVertexBuffer->Release();
			}
		}

		void _FlipSurface(IDirect3DTexture9 *texture) {
			g_pD3DDevice->SetTexture(0, texture);
			g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
		}

	} // End namespace HARDWARE
} // End namespace CORE