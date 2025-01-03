#include "globals.h"
#include <fstream>

// Define the constants
const int screenWidth = 1600;
const int screenHeight = 960;

// Define the other globals
string currentScene = "GAME";
string username = getUsernameFromFile();
vector<Enemy*> enemies;

Player player;
Map map;

string getUsernameFromFile() {
	string name;
	//read username from file(data/user.txt), if file does not exist, create it and write "Steve" to it
	ifstream file("data/user.txt");
	if (file.is_open())
	{
		file >> name;
		if(name.length() == 0) name = "Steve";
		file.close();
	}
	else
	{
		file.close();
		ofstream file("data/user.txt");
		file << "Steve";
		name = "Steve";
		file.close();
	}
	return name;
}