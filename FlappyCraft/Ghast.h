#include "Enemy.h"
#pragma once
class Ghast :public Enemy
{
public:
	int moveDir = 1;
	int range = 150;
	float moveSpeed = 1.0f;
	float xPosStart, yPosStart;
	int xScale = 64;
	int yScale = 64;

	Ghast(float x, float y) :Enemy(x, y) {
		xPosStart = x;
		yPosStart = y;
		enemyTexture = LoadTexture("assets/entities/ghast.png");
	}

	void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) override {
		move();
	}

	void move() {
		yPos += moveSpeed * moveDir;
		if (yPos >= yPosStart + range || yPos <= yPosStart - range) moveDir = -moveDir;
	}
};

