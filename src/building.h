#pragma once

#include "object.h"


enum class BuildingType {
	EASY = 0,
	HARD = 1,
	IMORTAL = 2
};

std::string buildingType_str(BuildingType type);

class Building : public Object {
protected:
	int _health;

public:
	Building(ObjectID id, Model& model, int health);

	virtual void interact(INTERACTION type);

	void kill();
};

class ImortalBuilding : public Building {
public:
	ImortalBuilding(ObjectID id, Model& model);

	virtual void interact(INTERACTION type);
};

class BuildingFactory {
public:
	static std::shared_ptr<Building> createBuilding(ObjectID id, Model& model, BuildingType type, int health);
};