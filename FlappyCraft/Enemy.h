#include "raylib.h"
#pragma once
class Enemy
{
	public:
		float xPos, yPos;
		int xScale = 64;
		int yScale = 64;

		Enemy(float x, float y) {
			xPos = x;
			yPos = y;
		}

		void draw() {
			DrawRectangle(xPos, yPos, xScale, yScale, ORANGE);
		}

		void move() {
			
		}
};

