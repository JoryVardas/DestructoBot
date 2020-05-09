build:
	cd src/DestructoBot/ && make

.PHONY: blender
blender:
	cd blender && ./blender_build.sh
