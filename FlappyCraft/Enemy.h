#include "raylib.h"
#include <iostream>
using namespace std;
#pragma once
class Enemy
{
	public:
		float xPos, yPos, xPosStart, yPosStart;
		int xScale = 64;
		int yScale = 64;
		int moveDir = 1;
		float moveSpeed;
		string type;

		Enemy(float x, float y, string ptype) {
			xPos = x;
			yPos = y;
			xPosStart = x;
			yPosStart = y;
			type = ptype;
			moveSpeed = init_speed();
		}

		float init_speed() {
			if (type == "BEE") return 2.0f;
			return 0;
		}

		void draw() {
			DrawRectangle(xPos, yPos, xScale, yScale, ORANGE);
		}

		void move() {
			if(type == "BEE") moveHover(yPosStart, 150);
		}

		void moveHover(float anchorHeight, int range) {
			yPos+=moveSpeed*moveDir;
			if(yPos >= anchorHeight + range || yPos <= anchorHeight - range) moveDir = -moveDir;
		}
};

