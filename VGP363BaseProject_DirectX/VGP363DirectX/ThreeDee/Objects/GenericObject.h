// GenericObject.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Components/Color.h"
#include "../Components/Constants.h"
#include "../Components/Vertex.h"
#include "../RayTracer/Misc/Ray.h"
#include "../RayTracer/Misc/ShadeRec.h"

namespace ThreeD
{
	class _GENERICOBJECT
	{
	public:


		_GENERICOBJECT();
		virtual ~_GENERICOBJECT();
		_GENERICOBJECT(const _GENERICOBJECT &object);
		
		virtual bool _Hit(const _RAY &ray, double &t, _SHADEREC &sr) = 0;

		void _SetColor(const _COLOR4F &c);
		void _SetColor(float a, float r, float g, float b);
		_COLOR4F _GetColor();
		_MATERIAL* _GetMaterial();
	protected:
		_COLOR4F color;
		_MATERIAL *material_ptr;
		_GENERICOBJECT& operator= (const _GENERICOBJECT &obj);

	};
}