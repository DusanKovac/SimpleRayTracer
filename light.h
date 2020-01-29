#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <vector>

using namespace std;

class Light {
	
	public:

		vector<float> location;
		vector<float> colour;


	Light(vector<float> start, vector<float> startdirection);
};
#endif