#pragma once
class Player{
	public:
		float xPos = -500;
		float yPos = 10;
		int xScale = 50;
		int yScale = 100;

		int speed = 3; //horizontal speed

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
};

