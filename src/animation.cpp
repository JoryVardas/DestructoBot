#include "animation.h"
#include "scene.h"


int Animation::_NextAnimId = 0;

int Animation::getNextAnimId() {
	return _NextAnimId++;
};

int Animation::getId() { return _animId; };

CameraRotateAnimation::CameraRotateAnimation(float totalAmount, int ticks) {
	_tick = 0;
	_numberTicks = ticks;
	_amountPerTick = totalAmount / ticks;
	_animId = Animation::getNextAnimId();
};


void CameraRotateAnimation::tick() {
	if (_tick >= _numberTicks) {
		AllowInput = true;
		_SCENE_.removeAnimation(_animId);
		return;
	};

	_SCENE_.camera().rotateAroundLookat(_amountPerTick);

	_tick++;
};

CharacterHeadRotateAnimation::CharacterHeadRotateAnimation(float totalAmount, int ticks) {
	_tick = 0;
	_numberTicks = ticks;
	_amountPerTick = totalAmount / ticks;
	_animId = Animation::getNextAnimId();
};


void CharacterHeadRotateAnimation::tick() {
	if (_tick >= _numberTicks) {
		AllowHeadMovement = true;
		_SCENE_.removeAnimation(_animId);
		return;
	};

	Model* head = _SCENE_.getCharacter().getChildModel("head");
	head->setRotation(0, 1, 0, head->getRotationAmount() + _amountPerTick);

	_tick++;
};



CharacterRotateAnimation::CharacterRotateAnimation(float totalAmount, int ticks) {
	_tick = 0;
	_numberTicks = ticks;
	_amountPerTick = totalAmount / ticks;
	_animId = Animation::getNextAnimId();
};


void CharacterRotateAnimation::tick() {
	if (_tick >= _numberTicks) {
		AllowHeadMovement = true;
		_SCENE_.removeAnimation(_animId);
		return;
	};

	Model& character = _SCENE_.getCharacter();
	character.setRotation(0, 1, 0, character.getRotationAmount() + _amountPerTick);

	_tick++;
};