#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

//classes
#include "Player.h"
#include "Map.h"
#include "Enemy.h"

//Global Variables
const int screenWidth = 1600;
const int screenHeight = 960;

string currentScreen = "GAME";

Player player;
Map map;
vector<Enemy> enemies;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Flappy Craft");
	SetTargetFPS(60);

	Camera2D camera = { 0 };
	camera.target = {player.xPos + player.xScale/2, player.yPos + player.yScale/2};
	camera.offset = {screenWidth/2, screenHeight/2};
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		player.updatePlayer(map);

		camera.target = {player.xPos + player.xScale/2, player.yPos + player.yScale / 2 };

		enemies = map.getEnemies();

		BeginDrawing();
			if (currentScreen == "GAME") {
				BeginMode2D(camera);
					ClearBackground(BLACK);
					map.drawMap();
					for (Enemy enemy : enemies)enemy.draw();
					DrawRectangle(player.xPos, player.yPos, player.xScale, player.yScale, player.pColor);
				EndMode2D();
			}
			else if (currentScreen == "DEATH") {
		
			}
			else if (currentScreen == "WIN") {

			}
			else if (currentScreen == "PAUSE") {
		
			}
			else if (currentScreen == "MENU") {
		
			}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}