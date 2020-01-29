#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "primitives.h"
#include "vector.h"
#include <vector>
#include "material.h"
using namespace std;

class Sphere: public Primitives {
	public:

		//Shape => sq(x-i)+sq(y-j)+sq(z-k)= sq(r)
		vector<float> center;
		float radius;
		Material* mat;


		Sphere(vector<float> center, float r, Material* m);
		double primitiveIntersect(vector<float> point, vector<float> direction);
};
#endif