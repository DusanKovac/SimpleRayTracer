#include "ray.h"
#include "light.h"
#include "vector.h"
#include "primitives.h"
#include "sphere.h"
#include "plane.h"
// #include "sphere.h"
#include "material.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>  
#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>


using namespace std;

#define WINDOW_SIDE  400
float FOV_X = 45;
#define FOV_Y 45
#define MAX_STEPS 4
#  define M_PI  3.14159265358979323846
const GLfloat  DegreesToRadians = M_PI / 180.0;


float PURPLE[3] = {1.0,0.0,0.33};
float NEWCOLOUR[3] = {0.1,0.8,0.8};
float PLANE[3] = {0.6,0.3,0.8};
float RED[3] = {0.9,0.2,0.1};
float SPEC[3] = {0.9,0.9,0.9};


	float ambientLight[3] = {.1,.1,.1};
	float ambientCoe = 0.37;


vector<Sphere> objectsList;


vector<Light> lightList;
vector<Plane> planeList;

vector<float> reflectVec(vector<float> r, vector<float> n){

	float rn = (r[1]*n[1])+(r[2]*n[2])+(r[0]*n[0]);
	
	vector<float> vrn = {2*rn*n[0]-r[0],2*rn*n[1]-r[1],2*rn*n[2]-r[2]};

	return vrn;
}



float ComputeLighting(vector<float> p, vector<float> n, vector<float> view, float kSpecular) {
    float i = ambientCoe;
	// bool intersection = false;
	uint k = 0;
	float d = 0;
	int o = 0;
	for(Light tmp = lightList[k]; k < lightList.size(); k++){
		vector<float> light = {tmp.location[0] - p[0], tmp.location[1] - p[1], tmp.location[2] - p[2]};
		float nl = (n[1]*light[1])+(n[2]*light[2])+(n[0]*light[0]);
		
		for(Sphere tmp = objectsList[o]; o < objectsList.size(); o++){
			float d = tmp.primitiveIntersect(p, light);
			if(d != -1){	
				break;
			}
			tmp = objectsList[o];
		}


		if(d != -1){	
			if(nl > 0){
				i += nl/(sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2])*sqrt(light[0]*light[0]+light[1]*light[1]+light[2]*light[2]));
			}
			if(kSpecular != -1){

				vector<float> r = {2*nl*n[0]-light[0],2*nl*n[1]-light[1],2*nl*n[2]-light[2]};
				float rv = (r[1]*view[1])+(r[2]*view[2])+(r[0]*view[0]);
				if(rv > 0){
					i+= pow(rv/(sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2])*sqrt(view[0]*view[0]+view[1]*view[1]+view[2]*view[2])),kSpecular);
				}

			}
		}

		tmp = lightList[k];
	}

    return i;
}

float* tracer(Ray r, int depth){

	bool intersection = false;
	float* resultColour;
	int k = 0;
	double i = 0;
	float reflective = 0;
	vector<float> p = {0.0, 0.0, 0.0};
	vector<float> n = {0.0, 0.0, 0.0};
	vector<float> view = {0.0, 0.0, 0.0};
	float t = 0; 
	t = planeList[0].primitiveIntersect(r.location, r.direction);

	if(t > 0){
		intersection = true;
	}


	for(Sphere tmp = objectsList[k]; k < objectsList.size(); k++){
		float d = tmp.primitiveIntersect(r.location, r.direction);
		if(d > 0.0000001 && d < t){	
			t = d;
			
			Sphere frontSphere = tmp;
			resultColour[0] = tmp.mat->colourDefuse[0];
			resultColour[1] = tmp.mat->colourDefuse[1];
			resultColour[2] = tmp.mat->colourDefuse[2];
			reflective = tmp.mat->kr;
			intersection = true;
			p.clear();
			n.clear();
			view.clear();


			p.push_back(r.location[0]+r.direction[0]*t); p.push_back(r.location[1]+r.direction[1]*t); p.push_back(r.location[2]+r.direction[2]*t);
			n.push_back(p[0]-frontSphere.center[0]); n.push_back(p[1]-frontSphere.center[1]); n.push_back(p[2]-frontSphere.center[2]);
			view.push_back(-1*r.direction[0]); view.push_back(-1*r.direction[1]); view.push_back(-1*r.direction[2]);

	
			i = ComputeLighting(p,n, view, tmp.mat->q);


		}
		tmp = objectsList[k];
	}

	if(intersection == false){	
		return ambientLight;
	}

	// printf("%f, %f, %f\n", resultColour[0],resultColour[1], resultColour[2]);

	resultColour[0]*=i;
	resultColour[1]*=i;
	resultColour[2]*=i;
	// printf("%f, %f, %f\n", resultColour[0],resultColour[1], resultColour[2]);
	if(depth == MAX_STEPS || reflective == 0 ){
		return resultColour;
	}
	
 	vector<float> reflection = reflectVec(view, n);
 	Ray newRay = Ray(p, reflection);
	float* reflect = tracer(newRay,depth+1);

	resultColour[0] =(1.0-reflective)*resultColour[0]+reflect[0]*reflective;
	resultColour[1] =(1.0-reflective)*resultColour[1]+reflect[1]*reflective;
	resultColour[2] =(1.0-reflective)*resultColour[2]+reflect[2]*reflective;

	return resultColour;
}
void scene1(){

	Material* bruh = new Material(PURPLE,SPEC,400,0,.5,1.5);
	Material* bruh2 = new Material(PURPLE,SPEC,2,0,.5,1.5);
	Material* aqua = new Material(NEWCOLOUR,SPEC,100,0,0.5,1.5);
	Material* red = new Material(RED,SPEC,32,0,0,1.5);
	Material* rede = new Material(NEWCOLOUR,SPEC,300,0.3,0.5,1.5);

	Sphere test = Sphere({0.1,1.2,7},1,aqua);
	Sphere test1 = Sphere({-2,1,4},1,bruh);
	Sphere test2 = Sphere({-.3,-.3,1},1,red);
	Sphere test3 = Sphere({2,1.1,4},1,bruh2);


	Plane temp = Plane({0,1,0,7},rede);

	planeList.push_back(temp);

	objectsList.push_back(test);
	objectsList.push_back(test1);
	objectsList.push_back(test3);
	objectsList.push_back(test2);
	Light newLight = Light({-4,0,-1},{1,0,0});
	lightList.push_back(newLight);
	ambientLight[0] = 0.1;
	ambientLight[1] = 0.1; 
	ambientLight[2] = 0.1;
	ambientCoe = 0.37;
}


void scene2(){

	Material* bruh = new Material(PURPLE,SPEC,32,0.5,.5,1.5);
	Material* aqua = new Material(NEWCOLOUR,SPEC,100,0,0.5,1.5);
	Material* red = new Material(RED,SPEC,32,0,0.5,1.5);
	Material* rede = new Material(PLANE,SPEC,30,0.3,0.5,1.5);

	Sphere test = Sphere({0,1,4},1,aqua);
	Sphere test1 = Sphere({1,1,2},1,bruh);
	Sphere test2 = Sphere({-.3,.5,2},.4,red);

	Sphere test3 = Sphere({-.3,-.3,1},1,red);


	Plane temp = Plane({0,1,0,8},rede);

	planeList.push_back(temp);

	objectsList.push_back(test);
	objectsList.push_back(test1);
	objectsList.push_back(test2);
	objectsList.push_back(test3);
	Light newLight = Light({-4,8,-1},{1,1,1});
	lightList.push_back(newLight);
	ambientLight[0] = 0.1;
	ambientLight[1] = 0.1; 
	ambientLight[2] = 0.1;
	ambientCoe = 0.37;
}
void scene4(){
	FOV_X = 20;

	Material* bruh = new Material(PURPLE,SPEC,32,0,.5,1.5);
	Material* aqua = new Material(NEWCOLOUR,SPEC,100,0.7,0.5,1.5);
	Material* red = new Material(RED,SPEC,32,0.3,0.3,1.5);
	Material* rede = new Material(PLANE,SPEC,30,0.9,0.5,1.5);

	Sphere test = Sphere({1,1,7},1,aqua);
	Sphere test1 = Sphere({2,1,4},1,bruh);
	Sphere test2 = Sphere({-2,4,8},3,red);
	Sphere test5 = Sphere({-1,1,3},1.3,rede);


	Plane temp = Plane({0,1,0,7},rede);

	planeList.push_back(temp);

	objectsList.push_back(test);
	objectsList.push_back(test1);
	objectsList.push_back(test2);
	objectsList.push_back(test5);
	objectsList.push_back(test2);
	Light newLight = Light({-4,0,-1},{1,0,0});
	Light newLight1 = Light({4,0,-1},{1,0,0});
	lightList.push_back(newLight);
	lightList.push_back(newLight1);
	ambientLight[0] = 0.1;
	ambientLight[1] = 0.1; 
	ambientLight[2] = 0.1;
	ambientCoe = 0.37;
}

void render(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	vector<float> startingPoint = {0,0,0};

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glColor3f(0,0,0);

	glBegin(GL_POINTS);
	for(int i = -WINDOW_SIDE; i < WINDOW_SIDE; i++){

		for(int j = -WINDOW_SIDE; j < WINDOW_SIDE; j++){

			vector<float> startingDirection = {((float)i)/WINDOW_SIDE, ((float)j)/WINDOW_SIDE, 1.0*((float) 1)/(2.0*tanf((FOV_X)/2.0))};
			Ray temp = Ray(startingPoint, startingDirection);

			glColor3fv(tracer(temp, 0));
			
			glVertex3fv(startingDirection.data());

		}

	}
	glEnd();
	glFlush();
}

void Options(unsigned char input, int x, int y){
    switch (input)
    {
    case 'q':
        exit(1); // quit the game
        break;
	}
}
int main(int argc,char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 

    printf("%s\n", argv[1]);


    if(strcmp(argv[1],"1")==0){
    	scene1();
    }
    else if(strcmp(argv[1],"2")==0){
    	scene2();
    }
    else {
	    scene4();	
    }
	glutInitWindowPosition(800, 300);
	glutInitWindowSize(WINDOW_SIDE, WINDOW_SIDE);
	glutCreateWindow("RayTrace");
	glutDisplayFunc(render);
	glutKeyboardFunc(Options);
	glutMainLoop();
}