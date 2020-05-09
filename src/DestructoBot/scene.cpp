#include "includes.h"
#include "model.h"
#include "scene.h"

float Scene::getCharacterX() { return _characterModel.getTransX(); };
float Scene::getCharacterY() { return _characterModel.getTransY(); };
float Scene::getCharacterZ() { return _characterModel.getTransZ(); };

Scene::Scene() {
	//_eyeX = 0;
	//_eyeY = 2;
	//_eyeY = 50;
	//_eyeZ = - 2;
	_camera = Camera(0, 3, -6, 0, 3, 1);
	_viewDist = 100;

	_charForwardX = 0;
	_charForwardZ = 1;
};
Scene::Scene(std::string propertyFilePath) {
	//_eyeX = 0;
	//_eyeY = 30;
	//_eyeZ = 0.0001;
	_camera = Camera(0, 3, -6, 0, 3, 1);
	_viewDist = 100;

	_charForwardX = 0;
	_charForwardZ = 1;

	_properties.load(propertyFilePath);
};

void Scene::addEnvironmentObject(std::shared_ptr<Object> obj) {
	_environmentObjects.push_back(obj);
};
void Scene::removeEnvironmentObject(ObjectID id) {
	int i = 0;
	for (; i < _environmentObjects.size(); i++) {
		if (_environmentObjects[i]->getId() == id) break;
	};
	if (i != _environmentObjects.size()) {
		_environmentObjects.erase(_environmentObjects.begin() + i);
	};
};

void Scene::setCharacterModel(Model& model) {
	_characterModel = model;
};

void Scene::moveCharacter(float x, float y, float z) {
	float newX = getCharacterX() + x;
	float newY = getCharacterY() + y;
	float newZ = getCharacterZ() + z;

	if (newX > _fenceX1 || newX < _fenceX2) return;
	if (newZ > _fenceZ1 || newZ < _fenceZ2) return;


	_characterModel.setTranslation(newX, newY, newZ);
	//_eyeX += x;
	//_eyeY += y;
	//_eyeZ += z;
	_camera.move(x, y, z, false);
};

void Scene::rotateCharacter(float amount) {
	_characterModel.setRotation(0, 1, 0, _characterModel.getRotationAmount() + amount);
};

void Scene::render() {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//specify our projection information
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Specify an orthographic projection mode.
	// The values used are perhaps a bit odd.
	//glOrtho(-12, 12, -12, 12, -12, 12); //!!
//	gluPerspective(60, WindowWidth / WindowHeight, 0.1, 30);
	gluPerspective(60, WindowWidth / WindowHeight, 0.1, _viewDist);

	//specify our lookat/eye and then draw our objects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	gluLookAt(_eyeX, _eyeY, _eyeZ, getCharacterX(), getCharacterY() + 2, getCharacterZ(), 0, 1, 0);
	_camera.draw();
//	gluLookAt(_eyeX, _eyeY, _eyeZ, 00.5, 0.5, 1, 0, 1, 0);
//	gluLookAt(_eyeX, _eyeY, _eyeZ, 0, 0, 0, 0, 1, 0);

	//render the models in the scene
	for (int i = 0; i < _environmentObjects.size(); i++) {
		_environmentObjects[i]->draw(getCharacterX(), getCharacterZ(), false);
	};

	//render the character
	_characterModel.draw(false);

	glutSwapBuffers();
};

///update to be in line with render
std::shared_ptr<Object> Scene::selectionRender(int x, int y) {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//specify our projection information
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Specify an orthographic projection mode.
	// The values used are perhaps a bit odd.
	//glOrtho(-12, 12, -12, 12, -12, 12); //!!
//	gluPerspective(60, WindowWidth / WindowHeight, 0.1, 30);
	gluPerspective(60, WindowWidth / WindowHeight, 0.1, _viewDist);

	//specify our lookat/eye and then draw our objects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	_camera.draw();
//	gluLookAt(_eyeX, _eyeY, _eyeZ, getCharacterX(), getCharacterY(), getCharacterZ(), 0, 1, 0);

	//render the models in the scene
	for (int i = 0; i < _environmentObjects.size(); i++) {
		_environmentObjects[i]->draw(getCharacterX(), getCharacterZ(), true);
	};

	//render the character
	_characterModel.draw(true);


	GLfloat buf[3];
	glReadPixels(x, WindowHeight - y, 1, 1, GL_RGB, GL_FLOAT, buf);
	std::printf("r: %i, g: %i, b: %i \n\n", (int)(buf[0] * 255), (int)(buf[1] * 255), (int)(buf[2] * 255));

	return getObjectById(ObjectID((int)(buf[0] * 255), (int)(buf[1] * 255), (int)(buf[2] * 255)));

	//glutSwapBuffers();
};

void Scene::update() {
	//first remove any removed animations
	for (int i = 0; i < _removedAnimations.size(); i++) {
		int found = -1;
		for (int j = 0; j < _animations.size(); j++) {
			if (_animations[j]->getId() == _removedAnimations[i]) {
				found = j;
				break;
			};
		};

		if (found > -1) {
			_animations.erase(_animations.begin() + found);
		};
	};

	//now update each animation
	for (int i = 0; i < _animations.size(); i++) {
		_animations[i]->tick();
	};
};


PropertyFile& Scene::getProperties() {
	return _properties;
};

void Scene::loadProperties(std::string propertyFilePath) {
	_properties.load(propertyFilePath);
};


std::shared_ptr<Object> Scene::getObjectById(ObjectID id) {
	for (int i = 0; i < _environmentObjects.size(); i++) {
		std::shared_ptr<Object> obj = _environmentObjects[i];
		if (obj->getId() == id) {
			return obj;
		};
	};

	//no object with that id exists in the scene.
	return null;
};





float Scene::getCharForwardX() { return _charForwardX; };
//float Scene::getCharForwardY() { return _charForwardY; };
float Scene::getCharForwardZ() { return _charForwardZ; };

void Scene::setCharForward(float x, float y, float z) {
	_charForwardX = x;
	//_charForwardY = y;
	_charForwardZ = z;
};

void Scene::moveCharacterForward(float amount) {
	moveCharacter(amount * _charForwardX, 0, amount * _charForwardZ);
};

Camera& Scene::camera() {
	return _camera;
};

void Scene::removeAnimation(int animId) {
	_removedAnimations.push_back(animId);
};

void Scene::turnCharacterLeft() {
	int charX = (int)_characterModel.getTransX();
	int charZ = (int)_characterModel.getTransZ();

	if ((charX % 12 != 0) || (charZ % 12 != 0)) return;


	if (_charForwardX == 1) {
		_charForwardX = 0;
		_charForwardZ = 1;
	}
	else if (_charForwardZ == 1) {
		_charForwardX = -1;
		_charForwardZ = 0;
	}
	else if (_charForwardX == -1) {
		_charForwardX = 0;
		_charForwardZ = -1;
	}
	else if (_charForwardZ == -1) {
		_charForwardX = 1;
		_charForwardZ = 0;
	};

	_animations.push_back(std::make_shared<CameraRotateAnimation>(-90, 30));
	_animations.push_back(std::make_shared<CharacterRotateAnimation>(-90, 30));
	//block futher input (the animation will reset this when it finishes).
	AllowInput = false;
};

void Scene::turnCharacterRight() {
	int charX = (int)_characterModel.getTransX();
	int charZ = (int)_characterModel.getTransZ();

	if ((charX % 12 != 0) || (charZ % 12 != 0)) return;


	if (_charForwardX == 1) {
		_charForwardX = 0;
		_charForwardZ = -1;
	}
	else if (_charForwardZ == 1) {
		_charForwardX = 1;
		_charForwardZ = 0;
	}
	else if (_charForwardX == -1) {
		_charForwardX = 0;
		_charForwardZ = 1;
	}
	else if (_charForwardZ == -1) {
		_charForwardX = -1;
		_charForwardZ = 0;
	};


	_animations.push_back(std::make_shared<CameraRotateAnimation>(90, 30));
	_animations.push_back(std::make_shared<CharacterRotateAnimation>(90, 30));
	//block futher input (the animation will reset this when it finishes).
	AllowInput = false;
};


void Scene::setFences(float x1, float x2, float z1, float z2) {
	_fenceX1 = x1;
	_fenceX2 = x2;
	_fenceZ1 = z1;
	_fenceZ2 = z2;
};

Model& Scene::getCharacter() {
	return _characterModel;
};

void Scene::addAnimation(std::shared_ptr<Animation> anim) {
	_animations.push_back(anim);
};


void Scene::placeCharacter(float x, float y, float z) {
	float curX = getCharacterX();
	float curY = getCharacterY();
	float curZ = getCharacterZ();

	_camera.move(-curX, -curY, -curZ, false);

	_characterModel.setTranslation(x, y, z);
};



Scene _SCENE_;