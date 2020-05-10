#pragma once

void keyPressedCallback(uchar key, int x, int y);
void specialKeyPressedCallback(int key, int x, int y);
void specialKeyUpCallback(int key, int x, int y);
void mouseButtonPressedCallback(int button, int state, int x, int y);
void drawSceneCallback();
void idleSceneCallback();
void resizeSceneCallback(int width, int height);