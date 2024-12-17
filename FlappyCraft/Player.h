#include <iostream>
using namespace std;
#include "Map.h"
#pragma once
class Player{
	public:
		float xPos = -500;
		float yPos = 10;
		int xScale = 50;
		int yScale = 50;
		Color pColor = BLACK;

		float speed = 1.5f; //horizontal speed

		float velocity = 0.0f; //the speed player is falling downwards
		float gravity = 0.5f; //how much the velocity is increasing
		float jumpStrength = 10.0f;

		void updatePos() {
			yPos += velocity;
			xPos += speed;
		}

		void jump() {
			velocity = -jumpStrength;
		}

		void applyGravity() {
			velocity += gravity;
		}

		int checkCollision(Map map) {
			pColor = BLACK;
			if (xPos > 0 && yPos+yScale > 0) {
				if (map.getElementByPos(yPos, xPos) == 1 || map.getElementByPos(yPos + yScale, xPos) == 1 || map.getElementByPos(yPos, xPos + xScale) == 1 || map.getElementByPos(yPos + yScale, xPos + xScale) == 1) {
					pColor = RED;
				}
				else if (map.getElementByPos(yPos, xPos) == 0 && map.getElementByPos(yPos + yScale, xPos) == 0 && map.getElementByPos(yPos, xPos + xScale) == 0 && map.getElementByPos(yPos + yScale, xPos + xScale) == 0) {
					pColor = BLUE;
				}
			}
			return 1;
		}
};

