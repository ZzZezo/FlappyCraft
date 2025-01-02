#include "gui.h"

const int heartsMargin = 2;
const int heartsSize = 32;

const float invSlotMargin = 10.0f;
const float invSlotSize = 75.0f;
const float invSlotBorderThickness = 7.0f;

Texture2D heartTexture;
Texture2D swapTexture;
Texture2D leftTexture, rightTexture;
Texture2D itemSword, itemTNT, itemTotem;

void loadGUITextures() {
	heartTexture = LoadTexture("assets/ui/heart.png");
	swapTexture = LoadTexture("assets/ui/swap.png");
	leftTexture = LoadTexture("assets/ui/left.png");
	rightTexture = LoadTexture("assets/ui/right.png");
	itemSword = LoadTexture("assets/items/sword.png");
	itemTNT = LoadTexture("assets/items/tnt.png");
	itemTotem = LoadTexture("assets/items/totem.png");
}

void drawGUI(int screenWidth, int screenHeight, Player player) {
	//health bar in top right corner
	for (int i = 0; i < player.maxHealth; i++)
	{
		//heart Positioning
		int x = screenWidth - heartsSize - heartsMargin - (i * (heartsSize + heartsMargin));
		int y = heartsMargin;

		if (i < (player.maxHealth - player.health))
			DrawTexture(heartTexture, x, y, BLACK);//empty heart
		else
			DrawTexture(heartTexture, x, y, WHITE);// full heart
	}
	//items in top left corner
	//first slot
	DrawRectangleLinesEx(Rectangle{ invSlotMargin, invSlotMargin, invSlotSize, invSlotSize }, invSlotBorderThickness, BLACK);
	DrawTexture(leftTexture, invSlotMargin, invSlotMargin * 2 + invSlotSize, WHITE);
	//swap
	DrawTexture(swapTexture, invSlotMargin * 2 + invSlotSize, invSlotMargin, player.swapColor);
	//second slot
	DrawRectangleLinesEx(Rectangle{ invSlotMargin * 3 + invSlotSize * 2, invSlotMargin, invSlotSize, invSlotSize }, invSlotBorderThickness, BLACK);
	DrawTexture(rightTexture, invSlotMargin * 3 + invSlotSize * 2, invSlotMargin * 2 + invSlotSize, WHITE);
}

void DrawItems(string Left, string Right) {
	if (Left == "SWORD") DrawTexture(itemSword, invSlotMargin + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);
	if (Right == "SWORD") DrawTexture(itemSword, invSlotMargin * 3 + invSlotSize * 2 + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);

	if (Left == "TNT") DrawTexture(itemTNT, invSlotMargin + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);
	if (Right == "TNT") DrawTexture(itemTNT, invSlotMargin * 3 + invSlotSize * 2 + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);

	if (Left == "TOTEM") DrawTexture(itemTotem, invSlotMargin + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);
	if (Right == "TOTEM") DrawTexture(itemTotem, invSlotMargin * 3 + invSlotSize * 2 + invSlotBorderThickness, invSlotMargin + invSlotBorderThickness, WHITE);
}