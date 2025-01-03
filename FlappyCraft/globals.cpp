#include "globals.h"

// Define the constants
const int screenWidth = 1600;
const int screenHeight = 960;

// Define the other globals
string currentScene = "GAME";
string username = "Steve";
std::vector<Enemy*> enemies;

Player player;
Map map;