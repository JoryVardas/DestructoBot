#include "includes.h"
#include <limits>

int WindowHeight = 600;
int WindowWidth = 600;
int WindowID = null;

std::string BinaryDirectory = "";



float DefaultBuildingDrawDist = 400;
float DefaultGroundDrawDist = 1200;
float FarBuildingDrawDist = 800;
float FarGroundDrawDist = 2400;
float BuildingDrawDist = DefaultBuildingDrawDist;
float GroundDrawDist = DefaultGroundDrawDist;

bool AllowInput = true;
bool AllowShooting = true;
bool AllowHeadMovement = true;

bool GamePaused = false;




std::vector<float> stringToFloatVector(std::string str) {
	size_t cur = 0;
	std::vector<float> ret;

	if (str.empty()) {
		return ret;
	};

	while (cur != std::string::npos) {
		size_t next = str.find_first_of(" ", cur);
		ret.push_back(std::atof(str.substr(cur, next).c_str()));
		if (next == std::string::npos) {
			cur = next;
		}
		else {
			cur = next + 1;
		};
	};

	return ret;
};

#pragma push_macro("min")
#undef min

bool floatEquals(float a, float b) {
	static float tolerance = 5 * std::numeric_limits<float>::min();
	return (a <= b + tolerance) && (a >= b - tolerance);
};


#pragma push_macro("pop")