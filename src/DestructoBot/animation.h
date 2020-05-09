#pragma once


#include "includes.h"
#include "camera.h"
#include "object.h"


class Animation {
private:
	static int _NextAnimId;
protected:
	int _tick;
	int _numberTicks;
	int _animId;

	static int getNextAnimId();
public:
	virtual void tick() = 0;

	int getId();
};

class CameraRotateAnimation : public Animation{
private:
	float _amountPerTick;
public:
	CameraRotateAnimation(float totalAmount, int ticks);

	virtual void tick();
};

class CharacterHeadRotateAnimation : public Animation {
private:
	float _amountPerTick;
public:
	CharacterHeadRotateAnimation(float totalAmount, int ticks);

	virtual void tick();
};

class CharacterRotateAnimation : public Animation {
private:
	float _amountPerTick;
public:
	CharacterRotateAnimation(float totalAmount, int ticks);

	virtual void tick();
};