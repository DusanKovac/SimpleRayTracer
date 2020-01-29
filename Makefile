rayT: rayT.cpp 
	g++ -Wall -g -c -o rayT.o rayT.cpp
	g++ -Wall -g -c -o ray.o ray.cpp
	g++ -Wall -g -c -o vector.o vector.cpp
	g++ -Wall -g -c -o primitives.o primitives.cpp
	g++ -Wall -g -c -o light.o light.cpp
	g++ -Wall -g -c -o sphere.o sphere.cpp
	g++ -Wall -g -c -o material.o material.cpp
	g++ -Wall -g -c -o plane.o plane.cpp
	g++ -Wall -g -o rayT rayT.o ray.o vector.o primitives.o sphere.o material.o light.o plane.o -lglut -lGLU -lGL
clean:
	rm ./rayT *.o