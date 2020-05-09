#include "vertex.h"
#include "includes.h"

Vertex::Vertex() {
	_x = _y = _z = 0;
	_nx = _ny = _nz = 0;
	_cr = _cg = _cb = _ca = 0;
};

Vertex::Vertex(const float x, const float y, const float z) {
	_x = x;
	_y = y;
	_z = z;
	_nx = _ny = _nz = 0;
	_cr = _cg = _cb = _ca = 0;
};

Vertex::Vertex(const float x, const float y, const float z, const float nx, const float ny, const float nz) {
	_x = x;
	_y = y;
	_z = z;
	_nx = nx;
	_ny = ny;
	_nz = nz;
	_cr = _cg = _cb = _ca = 0;
};

Vertex::Vertex(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float cr, const float cg, const float cb, const float ca) {
	_x = x;
	_y = y;
	_z = z;
	_nx = nx;
	_ny = ny;
	_nz = nz;
	_cr = cr;
	_cg = cg;
	_cb = cb;
	_ca = ca;
};

void Vertex::draw(bool disableColor) {
	glNormal3f(_nx, _ny, _nz);
	if (!disableColor) {
		glColor4f(_cr, _cg, _cb, _ca);
	};
	glVertex3f(_x, _y, _z);
};


float Vertex::x() { return _x; };
float Vertex::y() { return _y; };
float Vertex::z() { return _z; };

void Vertex::addColor(float r, float g, float b) {
	_cr += r;
	_cg += g;
	_cb += b;
	if (_cr > 1) _cr = 1;
	if (_cg > 1) _cg = 1;
	if (_cb > 1) _cb = 1;
}