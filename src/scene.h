#pragma once

#include <vector>
#include "object.h"
#include "propertyFile.h"
#include "camera.h"
#include "animation.h"

class Scene {
private:
	std::vector<std::shared_ptr<Object>> _environmentObjects;
	std::vector<std::shared_ptr<Animation>> _animations;
	std::vector<int> _removedAnimations;
	Model _characterModel;

	PropertyFile _properties;

	float _charForwardX;
	float _charForwardZ;

	float _fenceX1;
	float _fenceX2;
	float _fenceZ1;
	float _fenceZ2;

	float _viewDist;

	//float _eyeX;
	//float _eyeY;
	//float _eyeZ;
	Camera _camera;

public:
	Scene();
	Scene(std::string propertyFilePath);

	float getCharacterX();
	float getCharacterY();
	float getCharacterZ();

	void addEnvironmentObject(std::shared_ptr<Object> obj);
	void removeEnvironmentObject(ObjectID id);
	void setCharacterModel(Model& model);
	std::shared_ptr<Object> getObjectById(ObjectID id);

	void moveCharacter(float x, float y, float z);
	void moveCharacterForward(float amount);
	void rotateCharacter(float amount);

	float getCharForwardX();
	//float getCharForwardY();
	float getCharForwardZ();

	void setCharForward(float x, float y, float z);

	void render();
	std::shared_ptr<Object> selectionRender(int x, int y);
	void update();

	PropertyFile& getProperties();
	void loadProperties(std::string propertyFilePath);

	void turnCharacterLeft();
	void turnCharacterRight();

	void removeAnimation(int animId);

	Camera& camera();

	void setFences(float x1, float x2, float z1, float z2);
	Model& getCharacter();

	void addAnimation(std::shared_ptr<Animation> anim);

	void placeCharacter(float x, float y, float z);
};

extern Scene _SCENE_;