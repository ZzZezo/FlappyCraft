#include "Enemy.h"
#include "Bee.h"
#include "Skeleton.h"
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#pragma once

#define ID_DIRT 1
#define ID_GRASS 2
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
        Texture2D dirtTexture = LoadTexture("assets/blocks/dirt.png");
        Texture2D grassTexture = LoadTexture("assets/blocks/grass.png");

        Texture2D swordTexture = LoadTexture("assets/items/sword.png");
        Texture2D tntTexture = LoadTexture("assets/items/tnt.png");
        Texture2D totemTexture = LoadTexture("assets/items/totem.png");

        int map[WORLD_HEIGHT][WORLD_WIDTH] = {
            {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 0},
            {0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0},
            {0, 2, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}
        };

        void drawMap() {
            for (int y = 0; y < WORLD_HEIGHT; y++)
            {
                for (int x = 0; x < WORLD_WIDTH; x++)
                {
                    if (map[y][x] == ID_DIRT) {
                        DrawTexture(dirtTexture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
                    }
                    if (map[y][x] == ID_GRASS) {
                        DrawTexture(grassTexture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
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
                        DrawTexture(swordTexture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
                    }
                    if (map[y][x] == ID_TNT) {
                        DrawTexture(tntTexture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
                    }
                    if (map[y][x] == ID_TOTEM) {
                        DrawTexture(totemTexture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
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

