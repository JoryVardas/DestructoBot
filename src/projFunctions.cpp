#include "includes.h"
#include "projFunctions.h"
#include "callbackFunctions.h"
#include "loader.h"
#include "scene.h"

bool init(int argc, char** argv) {
	//we need to initialize our binary directory so we can load data.
	std::string exec_path = std::string(argv[0]);
	BinaryDirectory = exec_path.substr(0, exec_path.find_last_of("/"));

	//if there was no effect try '\\'
	if (BinaryDirectory == exec_path) {
		BinaryDirectory = exec_path.substr(0, exec_path.find_last_of("\\"));
	};

	if(BinaryDirectory != ""){
		BinaryDirectory .append("/");
	};

	//initialize opengl
	if (!glfwInit()) return false;

	WindowPtr = glfwCreateWindow(WindowWidth, WindowHeight, "DestructoBot", null, null);
	if (WindowPtr == null) return false;


	glfwMakeContextCurrent(WindowPtr);

	//Install our callback functions
	glfwSetWindowSizeCallback(WindowPtr, resizeSceneCallback);

	glfwSetMouseButtonCallback(WindowPtr, mouseButtonPressedCallback);
	glfwSetKeyCallback(WindowPtr, keyPressedCallback);


	//we need to set up some features of opengl
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

//	glEnable(GL_CULL_FACE);

	glShadeModel(GL_SMOOTH);
};


void load() {
	Loader::getLoader()->loadScene(_SCENE_);
};


void start() {
	//Define our main loop.
	while (!glfwWindowShouldClose(WindowPtr)) {
		_SCENE_.update();
		_SCENE_.render();

		glfwPollEvents();
	};
};


void cleanup() {
	if (WindowPtr != null) glfwTerminate();
};