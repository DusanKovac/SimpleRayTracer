#ifndef _RAY_H_
#define _RAY_H_
#include "vector.h"
#include <vector>

using namespace std;

class Ray {
	
	public:

		vector<float> direction;
		vector<float> location;


	Ray(vector<float> start, vector<float> startdirection);
};
#endif