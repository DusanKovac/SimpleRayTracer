#include "plane.h"
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

Plane::Plane(vector<float> coe, Material* m): coe(coe) {
	mat = m;
}


double Plane::primitiveIntersect(vector<float> point, vector<float> direction){


	float c = point[0]*coe[0] + point[1]*coe[1] + point[2]*coe[2] + coe[3]*1;

	float e = direction[0]*coe[0]+direction[1]*coe[1]+direction[2]*coe[2];



	if(e == 0){
		return -1;
	}


	double result = c/e;
	return result;

}

