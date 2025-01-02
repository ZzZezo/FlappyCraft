#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"

// Declare screen dimensions as extern constants
extern const int screenWidth;
extern const int screenHeight;

// Declare other globals
extern string currentScene;
extern std::vector<Enemy*> enemies;
extern Player player;
extern Map map;