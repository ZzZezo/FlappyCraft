#pragma once
#include <raylib.h>
#include "Player.h"

extern const int heartsMargin;
extern const int heartsSize;

extern const float invSlotMargin;
extern const float invSlotSize;
extern const float invSlotBorderThickness;

void loadGUITextures();

void drawGUI(int screenWidth, int screenHeight, Player player);

void DrawItems(string Left, string Right);