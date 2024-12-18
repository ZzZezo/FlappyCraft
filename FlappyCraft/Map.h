#include "Enemy.h"
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#pragma once

#define ID_BLOCK 1
#define ID_ENEMY 2
#define ID_ITEM 3

class Map{
	public:
        int tilesize = 64;
        int map[15][20] = {
            {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
            {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}
        };

        void drawMap() {
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == ID_BLOCK) {
                        DrawRectangle(x * tilesize, y * tilesize, tilesize, tilesize, GREEN);
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
                        DrawRectangle(x * tilesize, y * tilesize, tilesize, tilesize, WHITE);
                    }
                }
            }
        }

        //converts a 2D Position into the index in tileset
        int getElementByPos(float yPos,float xPos) {
            int yInd = floor(yPos / tilesize);
            int xInd = floor(xPos / tilesize);
            return map[yInd][xInd];
        }

        void deleteElementByPos(float yPos, float xPos) {
            int yInd = floor(yPos / tilesize);
            int xInd = floor(xPos / tilesize);
            map[yInd][xInd] = 0;
        }

        vector<Enemy> getEnemies() {
            vector<Enemy> enemies;
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == ID_ENEMY) {
                        enemies.push_back(Enemy(x * tilesize, y * tilesize));
                    }
                }
            }
            return enemies;
        }
};

