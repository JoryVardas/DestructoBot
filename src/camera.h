#pragma once

#include "includes.h"

class Camera {
private:
	float _x, _y, _z;
	float _lookatX, _lookatY, _lookatZ;

	float _calcX, _calcY, _calcZ;
	float _rotAmount;

public:
	Camera();
	Camera(float x, float y, float z);
	Camera(float x, float y, float z, float lookatX, float lookatY, float lookatZ);

	void move(float transX, float transY, float transZ, bool maintainLookat);
	void rotateAroundLookat(float amount);
	void resetRotation();

	void setLookat(float x, float y, float z);
	void setPosition(float x, float y, float z);

	void saveCalc();
	
	void draw();
};