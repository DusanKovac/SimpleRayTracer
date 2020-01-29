#include "ray.h"
#include <vector>

using namespace std;

Ray::Ray(vector<float> start, vector<float> startdirection): direction(startdirection), location(start) {}