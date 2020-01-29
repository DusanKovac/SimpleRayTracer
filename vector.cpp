#include "vector.h"
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;

	float vectorLength(vector<float> a){
		int length = sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
		return length;
	}
	vector<float> Normalise(vector<float> a){
		int length = vectorLength(a);
		vector<float> newVec;
		newVec[0] = a[0]/length;
		newVec[1] = a[1]/length;
		newVec[2] = a[2]/length;
		return newVec;
	}
	vector<float> calculatePoint(vector<float> point, vector<float> b){
		vector<float> newPoint;
		newPoint.push_back(point[0] + b[0]);
		newPoint.push_back(point[1] + b[1]);
		newPoint.push_back(point[2] + b[2]);

		return newPoint;
	}

	vector<float> vectorAddition(vector<float> a, vector<float> b){
		vector<float> newVector;
		newVector.push_back(a[0] + b[0]);
		newVector.push_back(a[1] + b[1]);
		newVector.push_back(a[2] + b[2]);

		return newVector;
	}
	vector<float> vectorSubtraction(vector<float> a, vector<float> b){
		vector<float> newVector;
		newVector.push_back(a[0] - b[0]);
		newVector.push_back(a[1] - b[1]);
		newVector.push_back(a[2] - b[2]);

		return newVector;
	}
	float vectorDotProduct(vector<float> a, vector<float> b){

		float dotProduct = (a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2]);
		return dotProduct;

	}
	vector<float> vectorReflection(vector<float> incident, vector<float> normal){
		vector<float> reflectedVector;

		incident = Normalise(incident);
		normal = Normalise(normal);

		reflectedVector = vectorSubtraction(incident,vectorScale(normal,2*vectorDotProduct(incident,normal)));

		return reflectedVector;

	}
	vector<float> vectorScale(vector<float> a, float scale){
		vector<float> newVec;
		newVec[0] = a[0] * scale;
		newVec[1] = a[1] * scale;
		newVec[2] = a[2] * scale;

		return newVec;
	}

	vector<float> calculateVector(vector<float> pointA, vector<float> pointB){
		vector<float> newVector;

		newVector.push_back(pointB[0] - pointA[0]);
		newVector.push_back(pointB[1] - pointA[1]);
		newVector.push_back(pointB[2] - pointA[2]);

		return newVector;
	}