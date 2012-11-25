// Iridescent.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BRDF.h"

namespace ThreeD
{
	class _IRIDESCENT : public _BRDF
	{
	public:
		_IRIDESCENT();
		_IRIDESCENT(const _IRIDESCENT &lambert);
		_IRIDESCENT& operator= (const _IRIDESCENT &lambert);
		~_IRIDESCENT();
		virtual _IRIDESCENT* _Clone();
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wo, const _VERTEX4F &wi);
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wo, _VERTEX4F &wi, _DOUBLE &pdf);
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo);
		void _SetKA(const _DOUBLE k);
		void _SetKD(const _DOUBLE k);
		void _SetCD(const _COLOR4F c);
		void _SetPower(const _DOUBLE p);
		void _SetRot(const _DOUBLE rot);
		_DOUBLE p_i;
		_DOUBLE r_i;
		_DOUBLE kd;
		_COLOR4F cd;
	};
}