#include "Map.h"
#include "Enemy.h"
#include "raylib.h"
#include <iostream>
#include <array>
using namespace std;
#include "sceneManager.h"
#pragma once

#define ID_DIRT 1
#define ID_SWORD 31
#define ID_TNT 32
#define ID_TOTEM 33

class Player{
	public:
		float xPos = -500;
		float yPos = 10;
		const int xScale = 50;
		const int yScale = 50;
		Color pColor = WHITE;

		const int maxHealth = 10;
		int health = maxHealth;
		int healthImmunityTimer = 0; //player can only be hurt when this is zero
		const int healthImmunityTimerMax = 30; //the value to reset the timer back to

		string LeftHand = "EMPTY";
		string RightHand = "TNT";
		string LastUsedHand = "NONE";
		Color swapColor = WHITE;

		float speed = 1.5f; //horizontal speed

		float velocity = 0.0f; //the speed player is falling downwards
		float gravity = 0.5f; //how much the velocity is increasing
		float jumpStrength = 10.0f;

		vector<Enemy*> enemiesCurrent;
		Map* mapCurrent;

		void updatePlayer(Map& map, vector<Enemy*>& enemies) {
			if(currentScene != "GAME") return;//dont update player if not in game
			applyGravity();

			enemiesCurrent = enemies;
			mapCurrent = &map;

			//check mouse input
			if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))useHandItem("LEFT"); //leftclick -> use item in left hand
			if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))useHandItem("RIGHT"); //rightclick -> use item in right hand
			
			if (IsKeyDown(KEY_F)) swapColor = ORANGE;

			if (IsKeyReleased(KEY_F)) { 
				swapHands(); 
				swapColor = WHITE;
			}

			if (IsKeyReleased(KEY_SPACE)){//check if player is jumping
				jump();
			}

			updatePos();
			updateColor();
			checkCollisionWithMap(map);
			checkCollisonWithEnemies(enemies);
			if(healthImmunityTimer>0) healthImmunityTimer--;
		}

		void updatePos() {
			yPos += velocity;
			xPos += speed;
		}

		void updateColor() {
			if(healthImmunityTimer>0) pColor = Color { 255, 160, 160, 255 };
			else pColor = WHITE;
		}

		void jump() {
			velocity = -jumpStrength; //negative velocity makes player move upward, "resets" velocity
		}

		void applyGravity() {
			velocity += gravity; //increase the velocity to simulate grvaity
		}

		int checkCollisionWithMap(Map& map) {
			if (xPos + xScale > 0 && yPos+yScale > 0) {
				if (checkCollisionType(ID_DIRT, map) > 0){
					getDamaged(1);
				}
				if (checkCollisionType(ID_GRASS, map) > 0) {
					getDamaged(1);
				}
				if (checkCollisionType(ID_SWORD ,map) > 0){
					pickUpItemByPos(ID_SWORD, map, "SWORD");
				}
				if (checkCollisionType(ID_TNT, map) > 0) {
					pickUpItemByPos(ID_TNT, map, "TNT");
				}
				if (checkCollisionType(ID_TOTEM, map) > 0) {
					pickUpItemByPos(ID_TOTEM, map, "TOTEM");
				}
				else if (checkCollisionType(0, map)){
					return 0; //returns 0 if not colliding with anything on the map
				}
			}
			return 1; //returns 1 if colliding with map
		}

		int checkCollisionType(int type, Map& map){
			//if collision detected, returns number between 1 and 4, depending on which part of the block was hit
			if(map.getElementByPos(yPos, xPos) == type) return 1;
			if(map.getElementByPos(yPos + yScale, xPos) == type) return 2;
			if(map.getElementByPos(yPos, xPos + xScale) == type) return 3;
			if(map.getElementByPos(yPos + yScale, xPos + xScale) == type) return 4;
			return 0;
		}

		void checkCollisonWithEnemies(vector<Enemy*>& enemies) {
			for (Enemy*& enemy : enemies) {
				if (xPos < enemy->xPos + enemy->xScale &&  //right side collision
					xPos + xScale > enemy->xPos &&       //left side collison
					yPos < enemy->yPos + enemy->yScale && //bottom side collision
					yPos + yScale > enemy->yPos) {       //top side collision

					if (!enemy->alive)return;
					//if colliding
					getDamaged(enemy->attackDamage);
				}
			}
		}

		void getDamaged(int dmg) {
			if(healthImmunityTimer>0) return;//dont damage player if he is ímmune
			if (dmg <= 0) return; //dont give immunity/red color if no damage is dealt
			health -= dmg;
			healthImmunityTimer = healthImmunityTimerMax;
			if(health <= 0) onDeath();
		}

		void onDeath() {
			if (LeftHand == "TOTEM" || RightHand == "TOTEM")
			{
				useTotem();
				return;
			}
			changeScene("DEATH"); //change to death/Game Over scene
		}

		void swapHands() {
			string temp = LeftHand;
			LeftHand = RightHand;
			RightHand = temp;
		}

		void useHandItem(string hand) {
			//function that runs on player click
			LastUsedHand = hand;
			if (hand == "LEFT") {
				useItem(LeftHand);
			}
			if (hand == "RIGHT") {
				useItem(RightHand);
			}
		}

		void useItem(string item) {
			//uses the item on being called, regardless if player clicked
			if(item == "EMPTY") return;
			if(item == "TEST") cout << "Test item used";
			if(item == "SWORD") attackMelee(128);
			if(item == "TNT") attackExplosion(128);
			if(item == "TOTEM") return;
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

		void attackMelee(int range) {
			//get all enemy objects with a distance smaller than range
			for (Enemy*& enemy : enemiesCurrent) {
				if (abs(xPos - enemy->xPos) < range && abs(yPos - enemy->yPos) < range)//check if distance smaller than range
				{
					//kill if killable
					if (!enemy->killable) return;
					enemy->die();
					if(LastUsedHand == "LEFT") LeftHand = "EMPTY";
					if(LastUsedHand == "RIGHT") RightHand = "EMPTY";
				}
			}
		}

		void attackExplosion(int range) {
			int yTile = floor(yPos / 64); //convert coordinate position into map-tileset pos
			int xTile = floor(xPos / 64); //convert coordinate position into map-tileset pos
			int rangeTile = floor(range / 64) + 1; //convert range position into map-tileset range
			cout << "Triggered an Explosion at Tile " << yTile << " " << xTile << " with a range of " << rangeTile << endl;
			killArea(yPos, xPos, range);
			mapCurrent->removeArea(yTile, xTile, rangeTile);
			if (LastUsedHand == "LEFT") LeftHand = "EMPTY";
			if (LastUsedHand == "RIGHT") RightHand = "EMPTY";
		}

		void killArea(int y, int x, int range) {
			//get all enemy objects with a distance smaller than range
			for (Enemy*& enemy : enemiesCurrent) {
				if (abs(x - enemy->xPos) < range && abs(y - enemy->yPos) < range)//check if distance smaller than range
				{
					//kill
					enemy->die();
				}
			}
		}

		void useTotem() {
			health = 3;
			healthImmunityTimer = healthImmunityTimerMax;

			if (LeftHand == "TOTEM") LeftHand = "EMPTY";
			else if (RightHand == "TOTEM") RightHand = "EMPTY";
		}
};

