#include "sphere.h"
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

Sphere::Sphere(vector<float> center, float r, Material* m): center(center), radius(r) {
	printf("%d\n", center[0]);
	mat = m;
}


double Sphere::primitiveIntersect(vector<float> point, vector<float> direction){


	//Shape => sq(x-i)+sq(y-j)+sq(z-k)= sq(r)

	vector<float> PC = vectorSubtraction(point, center);

	float a = vectorDotProduct(direction , direction);
	float b = 2*vectorDotProduct(vectorSubtraction(point, center), direction);
	float c = vectorDotProduct(vectorSubtraction(point, center), vectorSubtraction(point, center)) - radius*radius;

	double discriminant = b*b - 4*a*c;
	if(discriminant < 0){
		return -1;
	}

	double t1 = (-b + sqrt(discriminant))/(2*a);
	double t2 = (-b - sqrt(discriminant))/(2*a);

	if(t1 <= t2){
		return t1;
	}
	else{
		return t2;
	}
}

