#include "Enemy.h"
#include "Arrow.h"
#pragma once
class Skeleton:public Enemy
{
	public:
		int attackCooldown = 60;

		Skeleton(float x, float y) :Enemy(x, y) {
            attackDamage = 0;
            enemyTexture = LoadTexture("assets/entities/skeleton.png");
		}

        void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) override {
            attackCooldown--;
            if (attackCooldown <= 0) {
                attackCooldown = 300;
                newEnemies.push_back(new Arrow(xPos, yPos));//add to temporary container
            }
        }
};

