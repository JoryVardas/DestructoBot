#include "camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera() {
	_x = _y = _z = 0;
	_lookatX = _lookatY = 0;
	_lookatZ = -1;
	_rotAmount = 0;
	_calcX = _calcY = _calcZ = 0;
};
Camera::Camera(float x, float y, float z) {
	_calcX = _x = x;
	_calcY = _y = y;
	_calcZ = _z = z;
	_lookatX = _lookatY = 0;
	_lookatZ = -1;
	_rotAmount = 0;
};
Camera::Camera(float x, float y, float z, float lookatX, float lookatY, float lookatZ) {
	_calcX = _x = x;
	_calcY = _y = y;
	_calcZ = _z = z;
	_lookatX = lookatX;
	_lookatY = lookatY;
	_lookatZ = lookatZ;
	_rotAmount = 0;
};

void Camera::move(float transX, float transY, float transZ, bool maintainLookat) {
	_x += transX;
	_y += transY;
	_z += transZ;
	_calcX += transX;
	_calcY += transY;
	_calcZ += transZ;
	if (!maintainLookat) {
		_lookatX += transX;
		_lookatY += transY;
		_lookatZ += transZ;
	};
};
void Camera::rotateAroundLookat(float amount) {
	_rotAmount += amount;
	
	//calculate our location
	float x = _x - _lookatX;
	float y = _y - _lookatY;
	float z = _z - _lookatZ;
	
	//convert our rotation from degrees to radians
	float rad = _rotAmount * (M_PI / 180);

	//now do the matrix multiplication
	_calcX = (x * cos(rad)) + (z * sin(rad));
	_calcY = y;
	_calcZ = (z * cos(rad)) - (x * sin(rad));

	_calcX += _lookatX;
	_calcY += _lookatY;
	_calcZ += _lookatZ;
};
void Camera::resetRotation() {
	_rotAmount = 0;

	_calcX = _x;
	_calcY = _y;
	_calcZ = _z;
};

void Camera::setLookat(float x, float y, float z) {
	float amount = _rotAmount;
	resetRotation();

	_lookatX = x;
	_lookatY = y;
	_lookatZ = z;

	rotateAroundLookat(amount);
};
void Camera::setPosition(float x, float y, float z) {
	float amount = _rotAmount;
	resetRotation();

	_x = x;
	_y = y;
	_z = z;

	rotateAroundLookat(amount);
};

void Camera::saveCalc() {
	_x = _calcX;
	_y = _calcY;
	_z = _calcZ;
}

void Camera::draw() {
	gluLookAt(_calcX, _calcY, _calcZ, _lookatX, _lookatY, _lookatZ, 0, 1, 0);
};