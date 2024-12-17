#include "Enemy.h"
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#pragma once
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
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
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
                    if (map[y][x] == 1) {
                        DrawRectangle(x * tilesize, y * tilesize, tilesize, tilesize, GREEN);
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

        vector<Enemy> getEnemies() {
            vector<Enemy> enemies;
            for (int y = 0; y < 15; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (map[y][x] == 2) {
                        enemies.push_back(Enemy(x * tilesize, y * tilesize));
                    }
                }
            }
            return enemies;
        }
};

