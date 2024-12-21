#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;
#pragma once
class Enemy
{
	public:
		float xPos, yPos;
		int xScale;
		int yScale;

		Enemy(float x, float y) {
			xPos = x;
			yPos = y;
			xScale = 64;
			yScale = 64;
		}

		virtual void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) {}

		virtual void draw() {
			DrawRectangle(xPos, yPos, xScale, yScale, ORANGE);
		}
};

