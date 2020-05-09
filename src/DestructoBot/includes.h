#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#ifdef BUILD_WINDOWS
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#else

#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GL/glut.h>

#include <vector>
#include <string>
#include <memory>

#define null 0
#define uchar unsigned char

extern int WindowHeight;
extern int WindowWidth;
extern int WindowID;

extern std::string BinaryDirectory;


extern float BuildingDrawDist;
extern float GroundDrawDist;
extern float DefaultBuildingDrawDist;
extern float DefaultGroundDrawDist;
extern float FarBuildingDrawDist;
extern float FarGroundDrawDist;

extern bool AllowInput;
extern bool AllowShooting;
extern bool AllowHeadMovement;

extern bool GamePaused;


std::vector<float> stringToFloatVector(std::string);

template <typename T>
bool vectorContains(std::vector<T> vec, T val) {
	if (vec.size() == 0) return false;
	
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == val) return true;
	};

	return false;
};

bool floatEquals(float a, float b);

#endif