#include "Enemy.h"
#include "Arrow.h"
#pragma once
class Skeleton:public Enemy
{
	public:
		int attackCooldown = 60;

		Skeleton(float x, float y) :Enemy(x, y) {

		}

        void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) override {
            attackCooldown--;
            cout << attackCooldown << endl;
            if (attackCooldown <= 0) {
                attackCooldown = 300;
                newEnemies.push_back(new Arrow(xPos, yPos)); // Add to temporary container
            }
        }
};

