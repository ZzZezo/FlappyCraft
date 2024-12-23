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

		int attackDamage = 2;

		bool killable = true;
		bool alive = true;

		Texture2D enemyTexture;

		Enemy(float x, float y) {
			xPos = x;
			yPos = y;
			xScale = 64;
			yScale = 64;
		}

		virtual void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) {}

		virtual void draw() {
			DrawTexture(enemyTexture, xPos, yPos, WHITE);
		}

		void die() {
			alive = false;
			xPos = -1000;
		}
};

