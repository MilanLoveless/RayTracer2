// CORE.Hardware.3D.Texture.h
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
//#ifndef __CORE_HARDWARE_3D_TEXTURE_H_
//#define __CORE_HARDWARE_3D_TEXTURE_H_

//#include "CORE.Hardware.3D.h"

namespace CORE {
	namespace HARDWARE {

		struct TEXTUREINFO {
			int _nID;
			char *_pFileName;
			IDirect3DTexture9 *_pSurface;
			D3DSURFACE_DESC _SurfaceDesc;
			int _nWidth;
			int _nHeight;
			int _nActualWidth;
			int *_video;
			RECT _Rect;
		};

		TEXTUREINFO* _CreateTexture(int nID, int nWidth, int nHeight);
		TEXTUREINFO* _LoadTexture(int nID, char *strFilename, int nWidth, int nHeight);

		bool _LockTexture(TEXTUREINFO *pImage);

		void _UnlockTexture(TEXTUREINFO *pImage);

		void _UnloadTexture(TEXTUREINFO **ppInfo);

	} // End namespace HARDWARE
} // End namespace CORE
//#endif