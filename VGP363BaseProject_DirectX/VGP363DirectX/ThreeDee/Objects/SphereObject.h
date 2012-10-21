#pragma once

// This file contains the declaration of the class Sphere

#include "GenericObject.h"
#include "../Components/Vertex.h"


//-------------------------------------------------------------------------------- class Sphere
namespace ThreeD
{
	class _SPHERE: public _GENERICOBJECT {	
								  	
		public:
		
			_SPHERE(void);
				
			_SPHERE(_VERTEX4F c, double r);
			
			_SPHERE(_VERTEX4F c1, double r, _COLOR4F c2);

			_SPHERE(const _SPHERE& sphere);
		
			virtual _SPHERE* _Clone(void) const;

			virtual ~_SPHERE(void);   									

			_SPHERE& operator= (const _SPHERE& sphere);				
																					
			void _SetCenter(const _VERTEX4F& c);
		
			void _SetCenter(const double x, const double y, const double z);
		
			void _SetRadius(const double r);
						
			virtual bool _Hit(const _RAY& ray, double& t, _HITINFO &hit);	
		
		private:
	
			_VERTEX4F 	center;   			// center coordinates as a point  
			double 		radius;				// the radius 
		
			static const double kEpsilon;   // for shadows and secondary rays
	};

}

