#pragma once
#include "scene.h"
#include <string>
#include "propertyFile.h"
#include "model.h"
#include "building.h"
#include <map>

class Loader {
private:

	std::map<std::string, Model> _loadedModels;

	Model loadModel(std::string name);
	void loadCharacter(Scene& scene);
	void loadBuilding(Scene& scene, BuildingType type, float x, float y, float z, float sx, float sy, float sz);
	ObjectID generateId();
	void loadGround(Scene& scene);
	
	
	void generateSquare(Scene& scene, float centerX, float centerY, float width, float height, int max, int min);
	void generateMap(Scene& scene);
protected:
	static Loader* _inst;
	Loader();
	~Loader();
public:
	static Loader* getLoader();

	void loadScene(Scene& scene);
};