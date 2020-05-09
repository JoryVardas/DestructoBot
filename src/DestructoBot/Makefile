CC = g++
CCFLAGS =  -std=c++11 -I/usr/include/ -L/usr/lib/ -g
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

OBJS = animation.o building.o callbackFunctions.o camera.o includes.o loader.o model.o object.o polygon.o project.o projFunctions.o propertyFile.o scene.o vertex.o

test: $(OBJS)
	echo building
	$(CC) $(CCFLAGS) $^ -o ../Debug/$@ $(LIBRARIES)

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $< $(LIBRARIES)

## generate the prerequistes and append to the desired file
.prereq : $(OBJS:.o=.cpp) $(wildcard *.h) Makefile
	rm -f .prereq
	$(CC) $(CCFLAGS) -MM $(OBJS:.o=.cpp) >> ./.prereq

## include the generated prerequisite file
include .prereq