#include "loadScenes.h"
#include "globals.h"

int main(void) {
	InitWindow(screenWidth, screenHeight, "Flappy Craft");
	SetTargetFPS(60);

	loadGUITextures();
	loadScenes();

	while (!WindowShouldClose()) {
		sceneManager.update();
		sceneManager.draw();
	}

	CloseWindow();
	return 0;
}