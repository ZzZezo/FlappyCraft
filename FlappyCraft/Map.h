#include "Enemy.h"
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#pragma once

#define ID_BLOCK 1
#define ID_BEE 21
#define ID_ENEMY2 22
#define ID_ITEM 31

#define TILE_SIZE 64

class Map{
	public:
        int map[15][21] = {
            {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 0},
            {0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}
        };

        void drawMap() {
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == ID_BLOCK) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREEN);
                    }
                }
            }
        }

        void drawItems() {
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == ID_ITEM) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                    }
                }
            }
        }

        //converts a 2D Position into the index in tileset
        int getElementByPos(float yPos,float xPos) {
            int yInd = floor(yPos / TILE_SIZE);
            int xInd = floor(xPos / TILE_SIZE);
            return map[yInd][xInd];
        }

        void deleteElementByPos(float yPos, float xPos) {
            int yInd = floor(yPos / TILE_SIZE);
            int xInd = floor(xPos / TILE_SIZE);
            map[yInd][xInd] = 0;
        }

        vector<Enemy> getEnemies() {
            vector<Enemy> enemies;
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == ID_BEE) {
                        enemies.push_back(Enemy(x * TILE_SIZE, y * TILE_SIZE, "BEE"));
                    }
                    else if (map[y][x] == ID_ENEMY2) {
                        enemies.push_back(Enemy(x * TILE_SIZE, y * TILE_SIZE, "NONE"));
                    }
                }
            }
            return enemies;
        }
};

