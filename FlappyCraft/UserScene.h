#pragma once
#include "Scene.h"
#include "globals.h"
#include "raylib.h"
#include <fstream>

class UserScene : public Scene {
public:
    

    void update() override {
    }

    void draw() override {
        BeginDrawing();
            ClearBackground(BLUE);
            DrawText("Enter your username:", screenWidth/2-MeasureText("Enter your username:",40)/2, screenHeight / 2 - 100, 40, BLACK);
            DrawText(username.c_str(), screenWidth / 2 - MeasureText(username.c_str(), 40) / 2, screenHeight / 2, 40, WHITE);  // Display the username as the user types
            DrawText("Press Enter to confirm", screenWidth / 2 - MeasureText("Press Enter to confirm", 40) / 2, screenHeight / 2 + 100, 40, BLACK);
        EndDrawing();
    }

    void handleInput() override {
        // Handle user input (e.g., button click to go to menu or restart)
        if(IsKeyPressed(KEY_ENTER))
        {
            if(username.length()==0) username = "Steve";
            saveUsernameToFile();
            SceneManager::getInstance().changeScene("MENU");
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if(username.length()>0) username.pop_back();
        }
        for (int key = 32; key < 127; key++) {  // ASCII range for printable characters
            if (IsKeyPressed(key)) {
                if(username.length()>16) continue;
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) username += (char)key;
                else username += (tolower((char)key));
                break;
            }
        }
    }

    void saveUsernameToFile() {
		std::ofstream file("data/user.txt");
		file << username;
		file.close();
	}

    std::string getSceneName() const override {
        return "USER";
    }
};
