// BRDF.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once 

#include "../../Components/Color.h"
#include "../../Components/Vertex.h"
#include "../../RayTracer/Misc/ShadeRec.h"

namespace ThreeD
{
	class BRDF
	{
	public:
		virtual _COLOR4F _F(const _SHADEREC &sr, const _VERTEX4F &wi, const _VERTEX4F &wo) = 0;
		virtual _COLOR4F _SampleF(const _SHADEREC &sr, const _VERTEX4F &wi, _VERTEX4F &wo) = 0;
		virtual _COLOR4F _Rho(const _SHADEREC &sr, const _VERTEX4F &wo) = 0;

		_SAMPLER sampler_ptr;
	};

}