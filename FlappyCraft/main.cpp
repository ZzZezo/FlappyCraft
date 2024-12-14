#include "raylib.h"
#include <iostream>
using namespace std;

//classes
#include "Player.h"
#include "Map.h"

//Global Variables
const int screenWidth = 1600;
const int screenHeight = 960;

Player player;
Map map;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Flappy Craft");
	SetTargetFPS(60);

	Camera2D camera = { 0 };
	camera.target = {player.xPos + player.xScale/2, player.yPos + player.yScale/2};
	camera.offset = {screenWidth/2, screenHeight/2};
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		player.applyGravity();

		//check if player is jumping
		if (IsKeyReleased(KEY_SPACE)) {
			player.jump();
		}

		// Update player position
		player.updatePos();

		camera.target = {player.xPos + player.xScale/2, screenHeight/2};

		BeginDrawing();
		BeginMode2D(camera);
			ClearBackground(RAYWHITE);
			map.drawMap();
			DrawRectangle(player.xPos, player.yPos, player.xScale, player.yScale, RED);
		EndMode2D();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}