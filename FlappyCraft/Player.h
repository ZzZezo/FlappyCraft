#include "Map.h"
#include "raylib.h"
#include <iostream>
using namespace std;
#include "sceneManager.h"
#pragma once
class Player{
	public:
		float xPos = -500;
		float yPos = 10;
		const int xScale = 50;
		const int yScale = 50;
		Color pColor = BLUE;

		const int maxHealth = 10;
		int health = maxHealth;
		int healthImmunityTimer = 0; //player can only be hurt when this is zero
		const int healthImmunityTimerMax = 30; //the value to reset the timer back to

		float speed = 1.5f; //horizontal speed

		float velocity = 0.0f; //the speed player is falling downwards
		float gravity = 0.5f; //how much the velocity is increasing
		float jumpStrength = 10.0f;

		void updatePlayer(Map map) {
			if(currentScene != "GAME") return;//dont update player if not in game
			applyGravity();
			if (IsKeyReleased(KEY_SPACE)){//check if player is jumping
				jump();
			}
			updatePos();
			updateColor();
			checkCollision(map);
			if(healthImmunityTimer>0)healthImmunityTimer--;
		}

		void updatePos() {
			yPos += velocity;
			xPos += speed;
		}

		void updateColor() {
			if(healthImmunityTimer>0)pColor = RED;
			else pColor = BLUE;
		}

		void jump() {
			velocity = -jumpStrength;
		}

		void applyGravity() {
			velocity += gravity;
		}

		int checkCollision(Map map) {
			if (xPos + xScale > 0 && yPos+yScale > 0) {
				if (map.getElementByPos(yPos, xPos) == 1 || map.getElementByPos(yPos + yScale, xPos) == 1 || map.getElementByPos(yPos, xPos + xScale) == 1 || map.getElementByPos(yPos + yScale, xPos + xScale) == 1) {
					getDamaged(1);
				}
				if (map.getElementByPos(yPos, xPos) == 2 || map.getElementByPos(yPos + yScale, xPos) == 2 || map.getElementByPos(yPos, xPos + xScale) == 2 || map.getElementByPos(yPos + yScale, xPos + xScale) == 2) {
					getDamaged(2);
				}
				else if (map.getElementByPos(yPos, xPos) == 0 && map.getElementByPos(yPos + yScale, xPos) == 0 && map.getElementByPos(yPos, xPos + xScale) == 0 && map.getElementByPos(yPos + yScale, xPos + xScale) == 0) {
					return 0;
				}
			}
			return 1;
		}

		void getDamaged(int dmg) {
			if(healthImmunityTimer>0) return;//dont damage player if he is ímmune
			health -= dmg;
			healthImmunityTimer = healthImmunityTimerMax;
			if(health <= 0) onDeath();
		}

		void onDeath() {
			changeScene("DEATH");//change to death scene
		}
};

