#include <raylib.h>
#include "Player.h"
#pragma once

const int heartsMargin = 5;
const int heartsSize = 20;

void drawGUI(int screenWidth, int screenHeight, Player player) {
	//health bar in top right corner
	for (int i = 0; i < player.maxHealth; i++)
	{
		//heart Positioning
		int x = screenWidth - heartsSize - heartsMargin - (i * (heartsSize + heartsMargin));
		int y = heartsMargin;

		if (i < (10 - player.health))
			DrawRectangle(x, y, heartsSize, heartsSize, BLACK);//empty heart
		else
			DrawRectangle(x, y, heartsSize, heartsSize, RED);//full heart
	}
}