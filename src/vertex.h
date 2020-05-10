#pragma once

class Vertex {
private:
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _cr, _cg, _cb, _ca;
public:
	Vertex();
	Vertex(const float x, const float y, const float z);
	Vertex(const float x, const float y, const float z, const float nx, const float ny, const float nz);
	Vertex(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float cr, const float cg, const float cb, const float ca);

	void draw(bool disableColor);

	float x();
	float y();
	float z();

	void addColor(float r, float g, float b);
};