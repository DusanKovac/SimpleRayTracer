#ifndef _PLANE_H_
#define _PLANE_H_
#include "primitives.h"
#include "vector.h"
#include <vector>
#include "material.h"
using namespace std;

class Plane: public Primitives {
	public:

		//Shape => sq(x-i)+sq(y-j)+sq(z-k)= sq(r)
		vector<float> coe;
		Material* mat;


		Plane(vector<float> coe, Material* m);
		double primitiveIntersect(vector<float> point, vector<float> direction);
};
#endif