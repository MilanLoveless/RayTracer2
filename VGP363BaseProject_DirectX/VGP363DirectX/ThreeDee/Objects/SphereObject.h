#pragma once

// This file contains the declaration of the class Sphere

#include "GenericObject.h"
#include "../Components/Vertex.h"

//-------------------------------------------------------------------------------- class Sphere
namespace ThreeD
{
	class Sphere: public _GENERICOBJECT {	
								  	
		public:
		
			Sphere(void);   									// Default constructor
				
			Sphere(_VERTEX4F center, double r);					// Constructor 
					
			Sphere(const Sphere& sphere); 						// Copy constructor
		
			virtual Sphere* 									// Virtual copy constructor
			clone(void) const;

			virtual												// Destructor
			~Sphere(void);   									

			Sphere& 											// assignment operator
			operator= (const Sphere& sphere);				
																					
			void
			set_center(const _VERTEX4F& c);
		
			void
			set_center(const double x, const double y, const double z);
		
			void
			set_radius(const double r);
						
			virtual bool 												 
			hit(const _RAY& ray, double& t, _HITINFO &hit);	
		
		private:
	
			_VERTEX4F 	center;   			// center coordinates as a point  
			double 		radius;				// the radius 
		
			static const double kEpsilon;   // for shadows and secondary rays
	};

}

