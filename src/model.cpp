#include "includes.h"

#include "model.h"

Model::Model() {
	_rotX = _rotY = _rotZ = _rotAmount = 0;
	_transX = _transY = _transZ = 0;
	_scaleX = _scaleY = _scaleZ = 1;
	_visible = true;
};

Model::Model(std::vector<wPolygon>& mesh) {
	_mesh = mesh;
	_rotX = _rotY = _rotZ = _rotAmount = 0;
	_transX = _transY = _transZ = 0;
	_scaleX = _scaleY = _scaleZ = 1;
	_visible = true;
};

Model::Model(std::vector<wPolygon>& mesh, std::vector<Model> subModels) {
	_mesh = mesh;
	_subModels = subModels;
	_rotX = _rotY = _rotZ = _rotAmount = 0;
	_transX = _transY = _transZ = 0;
	_scaleX = _scaleY = _scaleZ = 1;
	_visible = true;
};

void Model::setRotation(const float x, const float y, const float z, const float amount) {
	_rotX = x;
	_rotY = y;
	_rotZ = z;
	_rotAmount = amount;
};

void Model::setTranslation(const float x, const float y, const float z) {
	_transX = x;
	_transY = y;
	_transZ = z;
};

void Model::setScale(const float x, const float y, const float z) {
	_scaleX = x;
	_scaleY = y;
	_scaleZ = z;
};

void Model::setMesh(std::vector<wPolygon> mesh) {
	_mesh = mesh;
};
void Model::setName(std::string name) {
	_name = name;
};

void Model::addSubModel(Model& model) {
	_subModels.push_back(model);
};

void Model::draw(bool overrideColor, float r, float g, float b, bool checkVertexInRange, float charX, float charZ) {

	//if we are not visible, dont do anything
	if (!_visible) return;

	//push whatever we have done previously.
	glPushMatrix();

	//perform translation, scale, rotation in that order (opengl requires we specify them in reverse order)
	glTranslatef(_transX, _transY, _transZ);
	glScalef(_scaleX, _scaleY, _scaleZ);
	glRotatef(_rotAmount, _rotX, _rotY, _rotZ);


	glBegin(GL_TRIANGLES);

	if (overrideColor) {
		glColor3f(r, g, b);
	}

	for (int i = 0; i < _mesh.size(); i++) {
		//if (checkVertexInRange) {
		//	float distx = charX - _mesh[i].centerX();
		//	float distZ = charZ - _mesh[i].centerZ();
		//
		//	if (((distx * distx) + (distZ * distZ)) < GroundDrawDist) {
		//		_mesh[i].draw(overrideColor);
		//	};
		//}
		//else {
			_mesh[i].draw(overrideColor);
		//};
	};

	glEnd();


	//go through the sub models and draw them
	for (int i = 0; i < _subModels.size(); i++) {
		if (checkVertexInRange) {
			float distx = charX - _subModels[i].getTransX();
			float distZ = charZ - _subModels[i].getTransZ();

			if (((distx * distx) + (distZ * distZ)) < GroundDrawDist) {
				_subModels[i].draw(overrideColor, r, g, b, checkVertexInRange, charX, charZ);
			};
		}
		else {
			_subModels[i].draw(overrideColor, r, g, b, checkVertexInRange, charX, charZ);
		}
	};

	//restore the previous transformations.
	glPopMatrix();
};

float Model::getTransX() { return _transX; };
float Model::getTransY() { return _transY; };
float Model::getTransZ() { return _transZ; };
float Model::getScaleX() { return _scaleX; };
float Model::getScaleY() { return _scaleY; };
float Model::getScaleZ() { return _scaleZ; };
float Model::getRotationAmount() { return _rotAmount; };

std::string Model::getName() { return _name; };

Model* Model::getSubModel(std::string path) {
	if (path == _name) return this;

	if (_name == path.substr(0, path.find_first_of("."))) {

		for (int i = 0; i < _subModels.size(); i++) {
			Model* ret = _subModels[i].getSubModel(path.substr(path.find_first_of('.') + 1));
			if (ret != null) return ret;
		};
	};

	return null;
};

Model* Model::getChildModel(std::string name) {
	for (int i = 0; i < _subModels.size(); i++) {
		if (_subModels[i].getName() == name) {
			return &_subModels[i];
		};
	};

	return null;
};


void Model::copy(Model& copyFrom) {
	_subModels = copyFrom._subModels;
	_mesh = copyFrom._mesh;
	_name = copyFrom._name;

	_rotX = copyFrom._rotX;
	_rotY = copyFrom._rotY;
	_rotZ = copyFrom._rotZ;
	_transX = copyFrom._transX;
	_transY = copyFrom._transY;
	_transZ = copyFrom._transZ;
	_scaleX = copyFrom._scaleX;
	_scaleY = copyFrom._scaleY;
	_scaleZ = copyFrom._scaleZ;
};


void Model::setVisibility(bool value) {
	_visible = value;
};

void Model::addColor(float r, float g, float b) {
	for (int i = 0; i < _mesh.size(); i++) {
		_mesh[i].addColor(r, g, b);
	}
	for (int i = 0; i < _subModels.size(); i++) {
		_subModels[i].addColor(r, g, b);
	};
}