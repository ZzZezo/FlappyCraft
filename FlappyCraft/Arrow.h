#include "Enemy.h"
#pragma once
class Arrow :public Enemy
{
	public:
		int moveDir = -1;
		float moveSpeed = 8.0f;

		Arrow(float x, float y) :Enemy(x, y) {
			xScale = 64;
			yScale = 16;
		}

		void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) override {
			move();
			killOffScreen(enemies);
		}

		void draw() {
			DrawRectangle(xPos, yPos, xScale, yScale, ORANGE);
		}

		void move() {
			xPos += moveSpeed * moveDir;
			//if(xPos >= 1920 || xPos <= 0) moveDir = -moveDir;
		}

		void killOffScreen(vector<Enemy*>& enemies) {
			//delete object (self) and remove from vector if it goes lower than x = -1000
			if (xPos < -1000) {
				enemies.erase(remove(enemies.begin(), enemies.end(), this), enemies.end());
				delete this;
			}
		}
};