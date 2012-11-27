// CORE.Hardware.3D.Texture.cpp
/////////////////////////////////////////////////////////////////////////////////////////

//#include "../GameCore.h"
#include "CORE.Hardware.3D.Texture.h"

namespace CORE {
	namespace HARDWARE {

		IDirect3DTexture9 *_CreateTexture(int nWidth, int nHeight) {
			IDirect3DTexture9 *pTexture;

			HRESULT hResult = D3DXCreateTexture(
				g_pD3DDevice, nWidth, nHeight, 1, 0, 
				D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture
			);
			if(FAILED(hResult))
			{
				//VERIFY(hResult);
		#ifdef _DEBUG
				DebugBreak();
		#endif
				return NULL;
			}

			return pTexture;
		}

		IDirect3DTexture9 *_LoadTexture(char *strFileName, int nWidth, int nHeight)
		{
			IDirect3DTexture9 *pTexture;
			D3DXIMAGE_INFO srcInfo;
			D3DCOLOR colorkey = 0x00000000;
			if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, strFileName, nWidth, nHeight, 1, 0, 
				D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 
				colorkey, &srcInfo, NULL, &pTexture)))
			{
				return NULL;
			}

			return pTexture;
		}

		TEXTUREINFO* _CreateTexture(int nID, int nWidth, int nHeight) {

			TEXTUREINFO *pImageInfo = new TEXTUREINFO;
			if(pImageInfo == NULL) return NULL;

			pImageInfo->_pSurface = _CreateTexture(nWidth, nHeight);
			if(pImageInfo->_pSurface == NULL) {
				delete pImageInfo;
				return NULL;
			}

			pImageInfo->_nID = nID;
			pImageInfo->_pFileName = "untitled.dat"; 
			pImageInfo->_pSurface->GetLevelDesc(0, &pImageInfo->_SurfaceDesc);
			pImageInfo->_nWidth = pImageInfo->_SurfaceDesc.Width;
			pImageInfo->_nActualWidth = 0;
			pImageInfo->_video = NULL;
			pImageInfo->_nHeight = pImageInfo->_SurfaceDesc.Height;
			pImageInfo->_Rect.top = 0;
			pImageInfo->_Rect.left = 0;
			pImageInfo->_Rect.right = pImageInfo->_nWidth;
			pImageInfo->_Rect.bottom = pImageInfo->_nHeight;

			return pImageInfo;
		}

		TEXTUREINFO* _LoadTexture(int nID, char *strFilename, int nWidth, int nHeight) {

			TEXTUREINFO *pImageInfo = new TEXTUREINFO;
			if(pImageInfo == NULL) return NULL;

			pImageInfo->_pSurface = _LoadTexture(strFilename, nWidth, nHeight);
			if(pImageInfo->_pSurface == NULL) {
				delete pImageInfo;
				return NULL;
			}

			pImageInfo->_nID = nID;
			pImageInfo->_pFileName = strFilename; 
			pImageInfo->_pSurface->GetLevelDesc(0, &pImageInfo->_SurfaceDesc);
			pImageInfo->_nWidth = pImageInfo->_SurfaceDesc.Width;
			pImageInfo->_nActualWidth = 0;
			pImageInfo->_video = NULL;
			pImageInfo->_nHeight = pImageInfo->_SurfaceDesc.Height;
			pImageInfo->_Rect.top = 0;
			pImageInfo->_Rect.left = 0;
			pImageInfo->_Rect.right = pImageInfo->_nWidth;
			pImageInfo->_Rect.bottom = pImageInfo->_nHeight;

			return pImageInfo;
		}

		void _UnloadTexture(TEXTUREINFO **ppInfo) {
			if(ppInfo == NULL) return;
			if(*ppInfo == NULL) return;
			if((*ppInfo)->_pSurface != NULL) {
				(*ppInfo)->_pSurface->Release();
			}
			delete *ppInfo;
			*ppInfo = NULL;
		}

		bool _LockTexture(TEXTUREINFO *pImage) {
			D3DLOCKED_RECT lock;
			if(pImage == NULL) {
				// Your texture was not loaded properly. Check the file name.
				return false;
			}
			HRESULT hResult = pImage->_pSurface->LockRect(0, &lock, &pImage->_Rect, D3DLOCK_NOSYSLOCK);
			if(!FAILED(hResult)) {
				pImage->_video = (int*)lock.pBits;
				pImage->_nActualWidth = ((unsigned int)lock.Pitch) >> 2;
			} else {
				// The texture could not be locked, possibly because it was already locked.
				//VERIFY(hResult);
				#ifdef _DEBUG
				DebugBreak();
				#endif
				pImage->_video = NULL;
				return false;
			}
			return true;
		}

		void _UnlockTexture(TEXTUREINFO *pImage) {
			pImage->_pSurface->UnlockRect(0);
			pImage->_video = NULL;
			pImage->_nActualWidth = 0;
		}

	} // End namespace HARDWARE
} // End namespace CORE