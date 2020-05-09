#pragma once

#include "vertex.h"

class wPolygon {
private:
	Vertex _v1, _v2, _v3;
	float _centerX, _centerY, _centerZ;
public:
	wPolygon(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	void draw(bool disableColor);

	float centerX();
	float centerY();
	float centerZ();

	void addColor(float r, float g, float b);
};