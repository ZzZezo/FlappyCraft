#include "raylib.h"
#include <iostream>
using namespace std;

//classes
#include "Player.h"

//Global Variables
const int screenWidth = 1600;
const int screenHeight = 900;

Player player;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Super Mario Flappy Craft");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		player.applyGravity();

		//check if player is jumping
		if (IsKeyReleased(KEY_SPACE)) {
			player.jump();
		}

		// Update player position
		player.updatePos();


		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(player.xPos, player.yPos, player.xScale, player.yScale, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}