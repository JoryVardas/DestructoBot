#include "includes.h"
#include "projFunctions.h"

int main(int argc, char** argv) {
	if (init(argc, argv)) {
		load();
		start();
	};
	cleanup();

	return 0;
};