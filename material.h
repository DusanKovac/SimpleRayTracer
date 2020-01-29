#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "vector.h"
#include <vector>

class Material {
	public:

	    float* colourDefuse;
	   	float* colourSpecular;
	    float q;
	    float kr;
	    float kt;
	    float refractI;

		Material(float* kd, float* ks, float q, float kr, float kt, float refractI);
};
#endif