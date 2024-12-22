#include "Enemy.h"
#include "Bee.h"
#include "Skeleton.h"
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#pragma once

#define ID_BLOCK 1
#define ID_BEE 21
#define ID_SKELETON 22
#define ID_SWORD 31
#define ID_TNT 32
#define ID_TOTEM 33

#define TILE_SIZE 64

#define WORLD_HEIGHT 15
#define WORLD_WIDTH 21

class Map{
	public:
        int map[WORLD_HEIGHT][WORLD_WIDTH] = {
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
            for (int y = 0; y < WORLD_HEIGHT; y++)
            {
                for (int x = 0; x < WORLD_WIDTH; x++)
                {
                    if (map[y][x] == ID_BLOCK) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREEN);
                    }
                }
            }
        }

        void drawItems() {
            for (int y = 0; y < WORLD_HEIGHT; y++)
            {
                for (int x = 0; x < WORLD_WIDTH; x++)
                {
                    if (map[y][x] == ID_SWORD) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                    }
                    if (map[y][x] == ID_TNT) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                    }
                    if (map[y][x] == ID_TOTEM) {
                        DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GOLD);
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

        vector<Enemy*> getEnemies() {
            vector<Enemy*> enemies;
            for (int y = 0; y < WORLD_HEIGHT; y++)
            {
                for (int x = 0; x < WORLD_WIDTH; x++)
                {
                    if (map[y][x] == ID_BEE) {
                        enemies.push_back(new Bee(x * TILE_SIZE, y * TILE_SIZE));
                    }
                    else if (map[y][x] == ID_SKELETON) {
                        enemies.push_back(new Skeleton(x * TILE_SIZE, y * TILE_SIZE));
                    }
                }
            }
            return enemies;
        }

        void removeArea(int y, int x, int range) {
            range--;//so it wont include 0 --> e.g. range of 2 will actually be 2 blocks excluding the center
            for (int row = y - range; row <= y + range; row++)
            {
                for (int col = x - range; col <= x + range; col++)
                {
                    if (row >= 0 && row < WORLD_HEIGHT && col >= 0 && col < WORLD_WIDTH)//check if out of bounds
                    {
                        map[row][col] = 0;
                    }
                }
            }
        }
};

