#include "building.h"
#include "scene.h"

std::string buildingType_str(BuildingType type) {
	switch (type) {
		case BuildingType::EASY:
			return std::string("BUILDING_TYPE_EASY");
		case BuildingType::HARD:
			return std::string("BUILDING_TYPE_HARD");
		case BuildingType::IMORTAL:
			return std::string("BUILDING_TYPE_IMORTAL");
		default:
			//this is never actually used, and should just cause an error.
			return std::string("BUILDING_TYPE_ERROR");
	};
};

Building::Building(ObjectID id, Model& model, int health) : Object(id, model) {
	_health = health;
};

void Building::interact(INTERACTION type) {
	switch (type) {
		case INTERACTION::ATTACKED:
			_health--;

			if (_health == 0) {
				kill();
			}
			else if (_health == 1) {
				_model.getChildModel("stage2")->setVisibility(false);
			}
			else if (_health == 2) {
				_model.getChildModel("stage1")->setVisibility(false);
			}
			break;
	};
};

void Building::kill() {
	//this is where we would set up the animation, but for now lets just remove the building.
	_SCENE_.removeEnvironmentObject(_id);
};

ImortalBuilding::ImortalBuilding(ObjectID id, Model& model) : Building(id, model, 0) {};

void ImortalBuilding::interact(INTERACTION type) {};


std::shared_ptr<Building> BuildingFactory::createBuilding(ObjectID id, Model& model, BuildingType type, int health) {
	if (type == BuildingType::IMORTAL) {
		return std::make_shared<ImortalBuilding>(id, model);
	};

	return std::make_shared<Building>(id, model, health);
};