// MappedLambert.h
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BRDF.h"
#include "../../../CORE/CORE.Hardware.3D.Texture.h"
#include "../Misc/Point2D.h"

namespace ThreeD
{
	class _MAPPEDLAMBERT : public _BRDF
	{
	public:
		_MAPPEDLAMBERT();
		_MAPPEDLAMBERT(const _MAPPEDLAMBERT &lambert);
		_MAPPEDLAMBERT& operator= (const _MAPPEDLAMBERT &lambert);
		~_MAPPEDLAMBERT();
		virtual _MAPPEDLAMBERT* _Clone();
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo);
		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetCD(const _COLOR4F c);
		void _CalculateCD(const _POINT2D &uv);
		_DOUBLE kd;
		_COLOR4F cd;
		CORE::HARDWARE::TEXTUREINFO *diffuse_map;
	};

}