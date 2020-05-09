#include "includes.h"
#include "callbackFunctions.h"

#include "scene.h"

void keyPressedCallback(uchar key, int x, int y) {
	if (!AllowInput) return;

	switch (key) {
		case 'z':
			if (GamePaused) return;
			_SCENE_.moveCharacterForward(1);
			break;
		case 'q':
			if (GamePaused) return;
			_SCENE_.turnCharacterLeft();
			break;
		case 'a':
			if (GamePaused) return;
			_SCENE_.turnCharacterRight();
			break;
		case 'p':
			if (GamePaused) GamePaused = false;
			else GamePaused = true;
			break;
		case 'r':
			if (GamePaused) return;
			_SCENE_.placeCharacter(0, 0, 0);
	}
};
void specialKeyPressedCallback(int key, int x, int y) {
	if (GamePaused) return;
	if (!AllowInput) return;
	float curRot = _SCENE_.getCharacter().getChildModel("head")->getRotationAmount();

	switch (key) {
		case GLUT_KEY_F1:
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
		case GLUT_KEY_F2:
			if (!AllowHeadMovement) break;
			if (floatEquals(curRot, 90)) break;
			else {
				AllowHeadMovement = false;
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
			}
			break;
		case GLUT_KEY_F3:
			if (!AllowHeadMovement) break;
			if (floatEquals(curRot, -90)) break;
			else {
				AllowHeadMovement = false;
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
			}
			break;
		case GLUT_KEY_F4:
			BuildingDrawDist = DefaultBuildingDrawDist;
			GroundDrawDist = DefaultGroundDrawDist;
			_SCENE_.camera().setPosition(0 + _SCENE_.getCharacterX(), 3, -6 + _SCENE_.getCharacterZ());

			AllowShooting = true;
			break;
		case GLUT_KEY_F5:
			BuildingDrawDist = DefaultBuildingDrawDist;
			GroundDrawDist = DefaultGroundDrawDist;
			_SCENE_.camera().setPosition(-6 + _SCENE_.getCharacterX(), 5, -6 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F6:
			BuildingDrawDist = DefaultBuildingDrawDist;
			GroundDrawDist = DefaultGroundDrawDist;
			_SCENE_.camera().setPosition(6 + _SCENE_.getCharacterX(), 5, -6 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F7:
			BuildingDrawDist = DefaultBuildingDrawDist;
			GroundDrawDist = DefaultGroundDrawDist;
			_SCENE_.camera().setPosition(-6 + _SCENE_.getCharacterX(), 5, 6 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F8:
			BuildingDrawDist = DefaultBuildingDrawDist;
			GroundDrawDist = DefaultGroundDrawDist;
			_SCENE_.camera().setPosition(6 + _SCENE_.getCharacterX(), 5, 12 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F9:
			BuildingDrawDist = FarBuildingDrawDist;
			GroundDrawDist = FarGroundDrawDist;
			_SCENE_.camera().setPosition(-12 + _SCENE_.getCharacterX(), 10, -12 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F10:
			BuildingDrawDist = FarBuildingDrawDist;
			GroundDrawDist = FarGroundDrawDist;
			_SCENE_.camera().setPosition(12 + _SCENE_.getCharacterX(), 10, -12 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F11:
			BuildingDrawDist = FarBuildingDrawDist;
			GroundDrawDist = FarGroundDrawDist;
			_SCENE_.camera().setPosition(-12 + _SCENE_.getCharacterX(), 10, 12 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;
		case GLUT_KEY_F12:
			BuildingDrawDist = FarBuildingDrawDist;
			GroundDrawDist = FarGroundDrawDist;
			_SCENE_.camera().setPosition(12 + _SCENE_.getCharacterX(), 10, 12 + _SCENE_.getCharacterZ());

			AllowShooting = false;
			break;

	}
};
void specialKeyUpCallback(int key, int x, int y) {
	if (GamePaused) return;
	if (!AllowInput) return;
	float curRot = _SCENE_.getCharacter().getChildModel("head")->getRotationAmount();

	switch (key) {
		case GLUT_KEY_F2:
			if (floatEquals(curRot, 0)) break;
			else if (floatEquals(curRot, 90)) {
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
			}
			else if (floatEquals(curRot, -90)) {
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
			}
			break;
		case GLUT_KEY_F3:
			if (floatEquals(curRot, 0)) break;
			else if (floatEquals(curRot, 90)) {
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(-90, 30));
			}
			else if (floatEquals(curRot, -90)) {
				_SCENE_.addAnimation(std::make_shared<CharacterHeadRotateAnimation>(90, 30));
			}
			break;
	}
};
void mouseButtonPressedCallback(int button, int state, int x, int y) {
	if (GamePaused) return;
	if (!AllowInput) return;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
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
void drawSceneCallback() {_SCENE_.render();};
void idleSceneCallback() {
	if (GamePaused) return;
	_SCENE_.update();
	_SCENE_.render();};
void resizeSceneCallback(int width, int height) {};