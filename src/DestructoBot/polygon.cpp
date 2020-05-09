#include "polygon.h"

wPolygon::wPolygon(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
	_v1 = v1;
	_v2 = v2;
	_v3 = v3;

	_centerX = (_v1.x() + _v2.x() + _v3.x()) / 3;
	_centerY = (_v1.y() + _v2.y() + _v3.y()) / 3;
	_centerZ = (_v1.z() + _v2.z() + _v3.z()) / 3;
};

void wPolygon::draw(bool disableColor) {
	//we do this in reverse order, since they are stored in the wrong direction.
	_v3.draw(disableColor);
	_v2.draw(disableColor);
	_v1.draw(disableColor);
};


float wPolygon::centerX() {	return _centerX; };
float wPolygon::centerY() { return _centerY; };
float wPolygon::centerZ() { return _centerZ; };

void wPolygon::addColor(float r, float g, float b) {
	_v1.addColor(r, g, b);
	_v2.addColor(r, g, b);
	_v3.addColor(r, g, b);
};