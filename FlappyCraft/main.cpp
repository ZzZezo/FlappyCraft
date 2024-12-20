#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

#include "gui.h"
#include "sceneManager.h"

//classes
#include "Player.h"
#include "Map.h"
#include "Enemy.h"

//Global Variables
const int screenWidth = 1600;
const int screenHeight = 960;

Player player;
Map map;
vector<Enemy*> enemies;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Flappy Craft");
	SetTargetFPS(60);

	Camera2D camera = { 0 };
	camera.target = {player.xPos + player.xScale/2, player.yPos + player.yScale/2};
	camera.offset = {screenWidth/2, screenHeight/2};
	camera.zoom = 1.0f;

	enemies = map.getEnemies();

	while (!WindowShouldClose()) {
		if (currentScene == "GAME") {
			player.updatePlayer(map, enemies);

			camera.target = { player.xPos + player.xScale / 2, player.yPos + player.yScale / 2 };

			vector<Enemy*> newEnemies;
			for (Enemy*& enemy : enemies) {
				enemy->update(enemies, newEnemies);
			}
			enemies.insert(enemies.end(), newEnemies.begin(), newEnemies.end());


			BeginDrawing();
				BeginMode2D(camera);
					ClearBackground(SKYBLUE);
					map.drawMap();
					map.drawItems();
					for (Enemy*& enemy : enemies) enemy->draw();
					DrawRectangle(player.xPos, player.yPos, player.xScale, player.yScale, player.pColor);
				EndMode2D();
				drawGUI(screenWidth, screenHeight, player);
			EndDrawing();
		}
		else if (currentScene == "DEATH") {
			BeginDrawing();
				ClearBackground(Color{224, 85, 85});
			EndDrawing();
		}
		else if (currentScene == "WIN") {

		}
		else if (currentScene == "PAUSE") {
		
		}
		else if (currentScene == "MENU") {
		
		}
	}

	CloseWindow();
	return 0;
}