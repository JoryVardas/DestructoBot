#pragma once

#include "includes.h"
#include "polygon.h"

#include <vector>
#include <string>

class Model {
private:
	std::vector<Model> _subModels;
	std::vector<wPolygon> _mesh;
	std::string _name;

	float _rotX, _rotY, _rotZ, _rotAmount;
	float _transX, _transY, _transZ;
	float _scaleX, _scaleY, _scaleZ;

	bool _visible;
public:
	Model();
	Model(std::vector<wPolygon>& mesh);
	Model(std::vector<wPolygon>& mesh, std::vector<Model> subModels);

	void setRotation(const float x, const float y, const float z, const float amount);
	void setTranslation(const float x, const float y, const float z);
	void setScale(const float x, const float y, const float z);
	void setName(std::string name);

	void setMesh(std::vector<wPolygon> mesh);

	void addSubModel(Model& model);

	void draw(bool overrideColor, float r = 0, float g = 0, float b = 0, bool checkVertexInRange = false, float charX = 0, float charZ = 0);

	float getTransX();
	float getTransY();
	float getTransZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	float getRotationAmount();
	std::string getName();

	Model* getSubModel(std::string path);
	Model* getChildModel(std::string name);

	void copy(Model& copyFrom);

	void setVisibility(bool value);

	void addColor(float r, float g, float b);
};