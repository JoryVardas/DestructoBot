#include "includes.h"
#include "callbackFunctions.h"

#include "scene.h"


void keyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (!AllowInput) return;

	//Handle basic functions
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_Z:
				if (GamePaused) return;
				_SCENE_.moveCharacterForward(1);
				break;
			case GLFW_KEY_Q:
				if (GamePaused) return;
				_SCENE_.turnCharacterLeft();
				break;
			case GLFW_KEY_A:
				if (GamePaused) return;
				_SCENE_.turnCharacterRight();
				break;
			case GLFW_KEY_P:
				if (GamePaused) GamePaused = false;
				else GamePaused = true;
				break;
			case GLFW_KEY_R:
				if (GamePaused) return;
				_SCENE_.placeCharacter(0, 0, 0);
		};
	};

	//handle special functions
	if (GamePaused) return;
	float curRot = _SCENE_.getCharacter().getChildModel("head")->getRotationAmount();

	if (action == GLFW_PRESS) {

		switch (key) {
			case GLFW_KEY_F1:
				if (!AllowHeadMovement) break;
				if (floatEquals(curRot, 0)) break;
				else if (floatEquals(curRot, 90)) {
					AllowHeadMovement = false;
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
				}
				else if (floatEquals(curRot, -90)) {
					AllowHeadMovement = false;
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
				}
				break;
			case GLFW_KEY_F2:
				if (!AllowHeadMovement) break;
				if (floatEquals(curRot, 90)) break;
				else {
					AllowHeadMovement = false;
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
				}
				break;
			case GLFW_KEY_F3:
				if (!AllowHeadMovement) break;
				if (floatEquals(curRot, -90)) break;
				else {
					AllowHeadMovement = false;
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
				}
				break;
			case GLFW_KEY_F4:
				BuildingDrawDist = DefaultBuildingDrawDist;
				GroundDrawDist = DefaultGroundDrawDist;
				_SCENE_.camera().setPosition(0 + _SCENE_.getCharacterX(), 3, -6 + _SCENE_.getCharacterZ());

				AllowShooting = true;
				break;
			case GLFW_KEY_F5:
				BuildingDrawDist = DefaultBuildingDrawDist;
				GroundDrawDist = DefaultGroundDrawDist;
				_SCENE_.camera().setPosition(-6 + _SCENE_.getCharacterX(), 5, -6 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F6:
				BuildingDrawDist = DefaultBuildingDrawDist;
				GroundDrawDist = DefaultGroundDrawDist;
				_SCENE_.camera().setPosition(6 + _SCENE_.getCharacterX(), 5, -6 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F7:
				BuildingDrawDist = DefaultBuildingDrawDist;
				GroundDrawDist = DefaultGroundDrawDist;
				_SCENE_.camera().setPosition(-6 + _SCENE_.getCharacterX(), 5, 6 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F8:
				BuildingDrawDist = DefaultBuildingDrawDist;
				GroundDrawDist = DefaultGroundDrawDist;
				_SCENE_.camera().setPosition(6 + _SCENE_.getCharacterX(), 5, 12 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F9:
				BuildingDrawDist = FarBuildingDrawDist;
				GroundDrawDist = FarGroundDrawDist;
				_SCENE_.camera().setPosition(-12 + _SCENE_.getCharacterX(), 10, -12 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F10:
				BuildingDrawDist = FarBuildingDrawDist;
				GroundDrawDist = FarGroundDrawDist;
				_SCENE_.camera().setPosition(12 + _SCENE_.getCharacterX(), 10, -12 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F11:
				BuildingDrawDist = FarBuildingDrawDist;
				GroundDrawDist = FarGroundDrawDist;
				_SCENE_.camera().setPosition(-12 + _SCENE_.getCharacterX(), 10, 12 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;
			case GLFW_KEY_F12:
				BuildingDrawDist = FarBuildingDrawDist;
				GroundDrawDist = FarGroundDrawDist;
				_SCENE_.camera().setPosition(12 + _SCENE_.getCharacterX(), 10, 12 + _SCENE_.getCharacterZ());

				AllowShooting = false;
				break;

		};
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_F2:
				if (floatEquals(curRot, 0)) break;
				else if (floatEquals(curRot, 90)) {
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
				}
				else if (floatEquals(curRot, -90)) {
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
				}
				break;
			case GLFW_KEY_F3:
				if (floatEquals(curRot, 0)) break;
				else if (floatEquals(curRot, 90)) {
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
				}
				else if (floatEquals(curRot, -90)) {
					_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
				}
				break;
		};
	};
};

void mouseButtonPressedCallback(GLFWwindow* window, int button, int action, int mods) {
	if (GamePaused) return;
	if (!AllowInput) return;

	double xpos = 0;
	double ypos = 0;
	glfwGetCursorPos(window, &xpos, &ypos);
	int x = floor(xpos);
	int y = floor(ypos);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (!AllowShooting) return;
		//_SCENE_.rotateCharacter(5);
		//_SCENE_.moveCharacter(0.5, 0, 0);
		std::shared_ptr<Object> obj = _SCENE_.selectionRender(x, y);
		//static float rot = 0;
		if (obj != null) {
			obj->interact(INTERACTION::ATTACKED);
			//obj->changeModelProperty("building", MODEL_PROPERTY::ROTATION, 0, 1, 0, rot);
			//rot += 10;
		};
	};
};

void resizeSceneCallback(GLFWwindow* window, int width, int height) {
	WindowWidth = width;
	WindowHeight = height;
	glViewport(0, 0, WindowWidth, WindowHeight);
};