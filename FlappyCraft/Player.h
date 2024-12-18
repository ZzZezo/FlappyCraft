#include "Map.h"
#include "raylib.h"
#include <iostream>
#include <array>
using namespace std;
#include "sceneManager.h"
#pragma once

#define ID_BLOCK 1
#define ID_ENEMY 2
#define ID_ITEM 3

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

		string LeftHand = "EMPTY";
		string RightHand = "EMPTY";

		float speed = 1.5f; //horizontal speed

		float velocity = 0.0f; //the speed player is falling downwards
		float gravity = 0.5f; //how much the velocity is increasing
		float jumpStrength = 10.0f;

		void updatePlayer(Map& map) {
			if(currentScene != "GAME") return;//dont update player if not in game
			applyGravity();

			//check mouse input
			if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))useHandItem("LEFT"); //leftclick -> use item in left hand
			if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))useHandItem("RIGHT"); //rightclick -> use item in right hand
			
			if(IsKeyReleased(KEY_F))swapHands();

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

		int checkCollision(Map& map) {
			if (xPos + xScale > 0 && yPos+yScale > 0) {
				if (checkCollisionType(ID_BLOCK, map) > 0){
					getDamaged(1);
				}
				if (checkCollisionType(ID_ENEMY ,map) > 0){
					getDamaged(2);
				}
				if (checkCollisionType(ID_ITEM ,map) > 0){
					pickUpItemByPos(ID_ITEM, map, "TEST");
				}
				else if (checkCollisionType(0, map)){
					return 0;
				}
			}
			return 1;
		}

		int checkCollisionType(int type, Map& map){
			if(map.getElementByPos(yPos, xPos) == type) return 1;
			if(map.getElementByPos(yPos + yScale, xPos) == type) return 2;
			if(map.getElementByPos(yPos, xPos + xScale) == type) return 3;
			if(map.getElementByPos(yPos + yScale, xPos + xScale) == type) return 4;
			return 0;
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

		void swapHands() {
			string temp = LeftHand;
			LeftHand = RightHand;
			RightHand = temp;
		}

		void useHandItem(string hand) {
			if (hand == "LEFT") {
				useItem(LeftHand);
			}
			if (hand == "RIGHT") {
				useItem(RightHand);
			}
		}

		void useItem(string item) {
			if (item == "EMPTY") return;
			if(item == "TEST") cout << "Test item used";
		}

		int pickUpItem(string item) {
			if(LeftHand == "EMPTY") LeftHand = item;
			else if(RightHand == "EMPTY") RightHand = item;
			else return 0; //returns 0 if player can't pick up item (inventory is full)
			return 1; //returns 1 if player picked the item up
		}

		void pickUpItemByPos(int itemID, Map& map, string item) {
			switch (checkCollisionType(itemID, map)) {
			case 1:
				if (pickUpItem(item) == 1) map.deleteElementByPos(yPos, xPos);
				break;
			case 2:
				if (pickUpItem(item) == 1) map.deleteElementByPos(yPos + yScale, xPos);
				break;
			case 3:
				if (pickUpItem(item) == 1) map.deleteElementByPos(yPos, xPos + xScale);
				break;
			case 4:
				if (pickUpItem(item) == 1) map.deleteElementByPos(yPos + yScale, xPos + xScale);
				break;
			}
		}
};

