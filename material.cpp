#include "material.h"

using namespace std;

	Material::Material(float* kd, float* ks, float q, float kr, float kt, float refractI): colourDefuse(kd), 
								colourSpecular(ks), q(q), kr(kr), kt(kt),refractI(refractI){}