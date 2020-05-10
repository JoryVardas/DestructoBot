#include "includes.h"
#include "projFunctions.h"
#include "callbackFunctions.h"
#include "loader.h"
#include "scene.h"

void init(int argc, char** argv) {
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
	glutInit(&argc, argv);

	//Specify our diplay mode
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//Initialize a window size, and create a window.
	glutInitWindowSize(WindowWidth, WindowHeight);

	WindowID = glutCreateWindow("DOOM : shoot bang!");

	//Install our callback functions
	glutDisplayFunc(&drawSceneCallback);
	glutIdleFunc(&idleSceneCallback);
	glutReshapeFunc(&resizeSceneCallback);

	glutMouseFunc(&mouseButtonPressedCallback);
	glutKeyboardFunc(&keyPressedCallback);
	glutSpecialFunc(&specialKeyPressedCallback);
	glutSpecialUpFunc(&specialKeyUpCallback);


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
	//Enter the opengl main loop
	glutMainLoop();
};


void cleanup() {};