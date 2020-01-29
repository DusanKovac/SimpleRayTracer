#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_
#include "ray.h"

class Primitives {
	
	public:

		Primitives();

		virtual double primitiveIntersect(vector<float> point, vector<float> direction) = 0;


};
#endif
