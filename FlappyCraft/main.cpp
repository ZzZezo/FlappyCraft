#include "raylib.h"
#include <iostream>
using namespace std;

//Global Variables
const int screenWidth = 1600;
const int screenHeight = 900;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Super Mario Flappy Craft");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
		//this is a test only for me understanding how git works with vs
	}
	CloseWindow();
	return 0;
}