#include "object.h"

ObjectID::ObjectID() {
	_r = 0;
	_g = 0;
	_b = 0;
};
ObjectID::ObjectID(int r, int g, int b) {
	_r = r;
	_g = g;
	_b = b;
};

int ObjectID::getR() {
	return _r;
};
int ObjectID::getG() {
	return _g;
};
int ObjectID::getB() {
	return _b;
};
float ObjectID::getRf() {
	return (float)_r / 255;
};
float ObjectID::getGf() {
	return (float)_g / 255;
};
float ObjectID::getBf() {
	return (float)_b / 255;
};

bool ObjectID::operator ==(ObjectID id) {
	return _r == id._r && _b == id._b && _g == id._g;
};

Object::Object(ObjectID id, Model& model) {
	_model = model;
	_id = id;
	_alwaysVisable = false;
};

ObjectID& Object::getId() {
	return _id;
};

Model& Object::getModel() {
	return _model;
};

void Object::draw(float charX, float charZ, bool idColor) {
	float charRelX = _model.getTransX() - charX;
	float charRelZ = _model.getTransZ() - charZ;


	if (_alwaysVisable || ((charRelX * charRelX) + (charRelZ * charRelZ)) <= BuildingDrawDist) {
		//when we pass the charX and charZ we actual translate them so that the object center is the origin point.
		_model.draw(idColor, _id.getRf(), _id.getGf(), _id.getBf(), _alwaysVisable, charX, charZ);
	};
};

void Object::interact(INTERACTION type) {};

void Object::changeModelProperty(std::string path, MODEL_PROPERTY prop, float a, float b, float c, float d) {
	Model* model = _model.getSubModel(path);
	if (model != null) {
		switch (prop) {
			case MODEL_PROPERTY::ROTATION:
				model->setRotation(a, b, c, d);
				break;
			case MODEL_PROPERTY::SCALE:
				model->setScale(a, b, c);
				break;
			case MODEL_PROPERTY::TRANSLATION:
				model->setTranslation(a, b, c);
				break;
		};
	};
};

void Object::setAlwaysVisable(bool val) {
	_alwaysVisable = val;
};