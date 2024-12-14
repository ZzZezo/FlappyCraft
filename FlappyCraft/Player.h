#pragma once
class Player{
	public:
		int xPos = 200;
		int yPos = 10;
		int xScale = 50;
		int yScale = 100;

		float velocity = 0.0f; //vertival speed
		float gravity = 0.5f; //strength of gravity
		float jumpStrength = 10.0f;

		void updatePos() {
			yPos += velocity;

		}

		void jump() {
			velocity = -jumpStrength;
		}

		void applyGravity() {
			velocity += gravity;
		}
};

