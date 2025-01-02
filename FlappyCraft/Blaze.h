#include "Enemy.h"
#include "Firecharge.h"
#pragma once
class Blaze :public Enemy
{
public:
    int attackCooldown = 60;

    Blaze(float x, float y) :Enemy(x, y) {
        attackDamage = 0;
        enemyTexture = LoadTexture("assets/entities/blaze.png");
    }

    void update(vector<Enemy*>& enemies, vector<Enemy*>& newEnemies) override {
        attackCooldown--;
        if (attackCooldown <= 0) {
            attackCooldown = 150;
            newEnemies.push_back(new Firecharge(xPos, yPos));//add to temporary container
        }
    }
};

