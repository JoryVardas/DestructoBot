#include "loader.h"
#include <fstream>
#include <vector>
#include <math.h>
#include <time.h>

Loader* Loader::_inst = null;
Loader::Loader() {};
Loader::~Loader() {};

Loader* Loader::getLoader() {
	if (_inst == null) {
		_inst = new Loader();
	}

	return _inst;
};

Model Loader::loadModel(std::string name) {

	if (_loadedModels.find(name) != _loadedModels.end()) {
		//std::printf("Model already loaded, cloning\n");
		//the model has already been loaded, so just copy it.
		Model m;
		m.copy(_loadedModels[name]);
		return m;
	};

	std::string filename = BinaryDirectory;
	std::printf("\nload model: %s \n", filename.c_str());
 	filename += std::string("data/");
	std::printf("\nload model: %s \n", filename.c_str());
	filename += name;
	std::printf("\nload model: %s \n", filename.c_str());
	filename += std::string(".model");
	std::printf("\nload model: %s \n", filename.c_str());

	Model base;
	base.setName(name);

	std::ifstream file;
	file.open(filename.c_str(), std::ifstream::in);

std::printf("%i\n", file.is_open());
	

	std::string line;
	Model* current = &base;

	bool readingMesh = false;

	while (std::getline(file, line)) {

		//if we arent already in a state to read the model data, wait until we are.
		if (line == "START_MODEL_DATA") {
			bool read_model_data = true;


			//if we are in a state to read teh model data, do so.
			while (read_model_data && std::getline(file, line)) {
				//while we are in the state to read the model data...

				if (line == "END_MODEL_DATA") {
					read_model_data = false;
					break;
				}
				else if (line.find("START_MESH") == 0) {
					//we are reading the mesh data.
					bool reading_mesh = true;
					std::vector<wPolygon> mesh;

					//get the path of the mesh and set the proper model to current
					std::string path = line.substr(line.find_first_of(" ") + 1);
					Model* model = base.getSubModel(path);
					if (model == null) {
						//the model we are reading the mesh for doesn't exist yet
						// (there may be several models in the path that dont exist)

						size_t prev_search_loc = 0;
						size_t cur_search_loc = 0;
						model = &base;

						while (model != null) {
							size_t next_search_loc = path.find_first_of(".", cur_search_loc);
							model = model->getSubModel(path.substr(cur_search_loc, next_search_loc));
							prev_search_loc = cur_search_loc;
							cur_search_loc = next_search_loc + 1;
						};

						//now we have the remainder of the path that we have to create.
						std::string remainder = path.substr(prev_search_loc);
						model = base.getSubModel(path.substr(0, prev_search_loc - 1));
						if (model == null) {
							//TODO
							//there was an error in the model file.
							throw std::runtime_error(std::string("ERROR IN MESH PATH"));
						}
						else {
							while (remainder.size() != 0) {
								cur_search_loc = remainder.find_first_of(".");
								Model m;
								m.setName(remainder.substr(0, cur_search_loc));
								model->addSubModel(m);
								model = model->getChildModel(m.getName());

								if (cur_search_loc == std::string::npos) {
									remainder = "";
								}
								else {
									remainder = remainder.substr(cur_search_loc + 1);
								};
							};
						};

						//now all the models on the path exist, and model have the last created one.
					};

					current = model;



					while (reading_mesh && std::getline(file, line)) {
						if (line == "END_MESH") {
							reading_mesh = false;
							break;
						};

						//get first vertex coordinate
						size_t space1 = line.find_first_of(' ');
						size_t space2 = line.find_first_of(' ', space1 + 1);

						float x1 = std::stof(line.substr(0, space1));
						float y1 = std::stof(line.substr(space1 + 1, space2));
						float z1 = std::stof(line.substr(space2+1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex normal
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float nx1 = std::stof(line.substr(0, space1));
						float ny1 = std::stof(line.substr(space1 + 1, space2));
						float nz1 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex color
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float cr1 = std::stof(line.substr(0, space1));
						float cg1 = std::stof(line.substr(space1 + 1, space2));
						float cb1 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;


						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float x2 = std::stof(line.substr(0, space1));
						float y2 = std::stof(line.substr(space1 + 1, space2));
						float z2 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex normal
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float nx2 = std::stof(line.substr(0, space1));
						float ny2 = std::stof(line.substr(space1 + 1, space2));
						float nz2 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex color
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float cr2 = std::stof(line.substr(0, space1));
						float cg2 = std::stof(line.substr(space1 + 1, space2));
						float cb2 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;


						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float x3 = std::stof(line.substr(0, space1));
						float y3 = std::stof(line.substr(space1 + 1, space2));
						float z3 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex normal
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float nx3 = std::stof(line.substr(0, space1));
						float ny3 = std::stof(line.substr(space1 + 1, space2));
						float nz3 = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						//get first vertex color
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float cr3 = std::stof(line.substr(0, space1));
						float cg3 = std::stof(line.substr(space1 + 1, space2));
						float cb3 = std::stof(line.substr(space2 + 1));

						//construct the polygon
						mesh.push_back(wPolygon(Vertex(x1, y1, z1,nx1,ny1,nz1,cr1, cg1, cb1, 0), Vertex(x2, y2, z2, nx2, ny2, nz2, cr2, cg2, cb2, 0), Vertex(x3, y3, z3, nx3, ny3, nz3, cr3, cg3, cb3, 0)));
					};

					current->setMesh(mesh);
				};
			};
		};
	
		if (line == "START_TRANSFORMATION_DATA") {
			bool read_transformation_data = true;


			//if we are in a state to read teh model data, do so.
			while (read_transformation_data && std::getline(file, line)) {
				//while we are in the state to read the model data...

				if (line == "END_TRANSFORMATION_DATA") {
					read_transformation_data = false;
					break;
				}
				else if (line.find("START_TRANSFORMATION") == 0) {
					//we are reading the mesh data.
					bool reading_transformation = true;

					//get the path of the mesh and set the proper model to current
					std::string path = line.substr(line.find_first_of(" ") + 1);
					Model* model = base.getSubModel(path);
					if (model == null) {
						//if we get here then there was an error in the data.

						//force crash
						model->getSubModel("");
					};

					current = model;



					while (reading_transformation && std::getline(file, line)) {
						if (line == "END_TRANSFORMATION") {
							reading_transformation = false;
							break;
						};

						
						size_t space1 = line.find_first_of(' ');
						size_t space2 = line.find_first_of(' ', space1 + 1);

						float transX = std::stof(line.substr(0, space1));
						float transY = std::stof(line.substr(space1 + 1, space2));
						float transZ = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);

						float scaleX = std::stof(line.substr(0, space1));
						float scaleY = std::stof(line.substr(space1 + 1, space2));
						float scaleZ = std::stof(line.substr(space2 + 1));

						//we need to read the next line and repeat the above;
						if (!std::getline(file, line)) break;
						
						space1 = line.find_first_of(' ');
						space2 = line.find_first_of(' ', space1 + 1);
						size_t space3 = line.find_first_of(' ', space2 + 1);

						float rotX = std::stof(line.substr(0, space1));
						float rotY = std::stof(line.substr(space1 + 1, space2));
						float rotZ = std::stof(line.substr(space2 + 1, space3));
						float rotAmount = std::stof(line.substr(space3 + 1));

						current->setTranslation(transX, transY, transZ);
						current->setScale(scaleX, scaleY, scaleZ);
						current->setRotation(rotX, rotY, rotZ, rotAmount);
					};
				};
			};
		};
	};

	file.close();

	_loadedModels[name] = base;

	return base;
};


void Loader::loadCharacter(Scene& scene) {

	Model m = loadModel(scene.getProperties()["CHARACTER_MODEL"]);
	scene.setCharacterModel(m);
};

ObjectID Loader::generateId() {
	static int curr = 0;
	static int curg = 0;
	static int curb = 0;
	if (curg == 255) {
		curg = 0;
		curb++;
	};
	if (curr == 255) {
		curr = 0;
		curg++;
	};
	curr++;

	return ObjectID(curr, curg, curb);
};


void Loader::loadBuilding(Scene& scene, BuildingType type, float x, float y, float z, float sx, float sy, float sz) {
	//generate a random color to add to the model color.
	float amount = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float randR = amount * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float randG = amount * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float randB = amount * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

	//printf("randr: %f, randg: %f, randb: %f\n", randR, randG, randB);

	Model model = loadModel(scene.getProperties()[buildingType_str(type) + "_MODEL"]);
	model.addColor(randR, randG, randB);
	model.setTranslation(model.getTransX() + x, model.getTransY() + y, model.getTransZ() + z);
	model.setScale(model.getScaleX() * sx, model.getScaleY() * sy, model.getScaleZ() * sz);

	//generate a random rotation for this building.
	float rot = (float)(rand() % (359 + 1));
	if (rot >= 0 && rot < 90) rot = 0;
	else if (rot >= 90 && rot < 180) rot = 90;
	else if (rot >= 180 && rot < 270) rot = 180;
	else if (rot >= 270) rot = 270;
	model.setRotation(0, 1, 0, rot);

	std::shared_ptr<Building> building = BuildingFactory::createBuilding(Loader::generateId(), model, type, (atoi(scene.getProperties()[buildingType_str(type) + "_HEALTH"].c_str())));
	scene.addEnvironmentObject(building);
};

void Loader::generateSquare(Scene& scene, float centerX, float centerY, float width, float height, int max, int min) {


	int num_buildings = (rand() % ((max + 1) - min)) + min;

	float subsquare_width = width / num_buildings;
	float subsquare_height = height / num_buildings;

	centerX += subsquare_width / 2;
	centerY += subsquare_height / 2;

	std::vector<int> occupied_x;
	std::vector<int> occupied_y;

	for (int i = 0; i < num_buildings; i++) {
		int x;
		int y;
		do {
			x = (rand() % (num_buildings));
			y = (rand() % (num_buildings));
		} while (vectorContains(occupied_x, x) && vectorContains(occupied_y, y));

		occupied_x.push_back(x);
		occupied_y.push_back(y);
		//x = 0;
		//y = 0;

		BuildingType buildingType = (BuildingType)((rand() % ((2 + 1) - 0)) + 0);
		loadBuilding(scene, buildingType, ((x ) * subsquare_width) + centerX, 0, ((y) * subsquare_height) + centerY, 1/(float)num_buildings, 1, 1/(float)num_buildings);

		//loadEnvironmentModel(scene, "building", centerX, 0, centerY, 1.0 , 1.0, 1);
	};
};

void Loader::loadGround(Scene& scene) {
	Model model = loadModel(scene.getProperties()["GROUND_MODEL"]);
	std::shared_ptr<Object> obj = std::make_shared<Object>(generateId(), model);
	obj->setAlwaysVisable(true);
	scene.addEnvironmentObject(obj);
}


void Loader::generateMap(Scene& scene) {
	int num_squares = std::atoi(scene.getProperties()["MAP_NUMBER_SQUARES"].c_str());
	float square_width = std::atof(scene.getProperties()["MAP_SQUARE_WIDTH"].c_str());
	float square_height = std::atof(scene.getProperties()["MAP_SQUARE_HEIGHT"].c_str());
	float road_width = std::atof(scene.getProperties()["MAP_ROAD_WIDTH"].c_str());
	int max_buildings = std::atoi(scene.getProperties()["MAP_MAX_BUILDINGS_IN_SQUARE"].c_str());
	int min_buildings = std::atoi(scene.getProperties()["MAP_MIN_BUILDINGS_IN_SQUARE"].c_str());
	std::vector<float> generator_points_x = stringToFloatVector(scene.getProperties()["MAP_GENERATOR_POINTS_X"]);
	std::vector<float> generator_points_y = stringToFloatVector(scene.getProperties()["MAP_GENERATOR_POINTS_Z"]);

	//we are first going to load the ground into the scene.
	//loadEnvironmentObject(scene, scene.getProperties()["GROUND_MODEL"], 0, -0, 0);
	loadGround(scene);

	for (int i = 0; i < num_squares; i++) {
		generateSquare(scene, generator_points_x[i], generator_points_y[i], square_width, square_height, max_buildings, min_buildings);
	};
};

void Loader::loadScene(Scene& scene) {
	srand(time(null));
	scene.loadProperties(BinaryDirectory + "data/scene.prop");

	std::vector<float> fenceX = stringToFloatVector(scene.getProperties()["FENCE_X"]);
	std::vector<float> fenceZ = stringToFloatVector(scene.getProperties()["FENCE_Z"]);

	scene.setFences(fenceX[0], fenceX[1], fenceZ[0], fenceZ[1]);

	//next we want to generate a building map
	generateMap(scene);
	


	loadCharacter(scene);
};