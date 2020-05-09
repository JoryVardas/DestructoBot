#pragma once

#include "model.h"

enum class INTERACTION {
	ATTACKED
};

enum class MODEL_PROPERTY {
	SCALE,
	ROTATION,
	TRANSLATION
};

class ObjectID {
private:
	int _r;
	int _g;
	int _b;
public:
	ObjectID();
	ObjectID(int r, int g, int b);

	int getR();
	int getG();
	int getB();
	float getRf();
	float getGf();
	float getBf();

	bool operator ==(ObjectID id);
};

class Object {
protected:
	Model _model;
	ObjectID _id;
	bool _alwaysVisable;
public:
	Object(ObjectID id, Model& model);

	ObjectID& getId();
	Model& getModel();
	void draw(float charX, float charZ, bool idColor);

	void changeModelProperty(std::string path, MODEL_PROPERTY prop, float a, float b, float c, float d);

	virtual void interact(INTERACTION type);

	void setAlwaysVisable(bool);
};