#ifndef _VECTOR_H_
#define _VECTOR_H_	
#include <vector>
using namespace std;


	vector<float> Normalise(vector<float> a);
	float vectorLength(vector<float> a);
	vector<float> vectorScale(vector<float> a, float scale);

	vector<float> vectorReflection(vector<float> incident, vector<float> normal);
	vector<float> calculateVector(vector<float> pointA, vector<float> pointB);
	vector<float> calculatePoint(vector<float> point, vector<float> b);
	vector<float> vectorCrossProduct(vector<float> a, vector<float> b);
	vector<float> vectorAddition(vector<float> a, vector<float> b);
	vector<float> vectorSubtraction(vector<float> a, vector<float> b);
	float vectorDotProduct(vector<float> a, vector<float> b);

#endif