#pragma once
#include "Scene.h"
#include "globals.h"
#include "raylib.h"
#include <fstream>
#include <vector>

class HighscoreScene : public Scene {
public:
    std::vector<std::string> lines;
    std::string line;

    Rectangle exitButton = { 100, (float)screenHeight - 150, 250, 60 };
    Color exitButtonColor = GRAY;

    void update() override {
        lines.clear();
        ifstream file("data/rankings.txt");
        for (int i = 0; i < 10 && std::getline(file, line); ++i) {
            lines.push_back(line);
        }
        file.close();
    }

    void draw() override {
        BeginDrawing();
            ClearBackground(BLUE);
            DrawText("Highscores:",100, 100, 50, WHITE);
            for (int i = 0; i < lines.size(); ++i) {
                DrawText((std::to_string(i+1) + ". " + lines[i]).c_str(), 175, 200 + i * 55 , 50, LIGHTGRAY);
            }
            DrawRectangleRec(exitButton, exitButtonColor);
            DrawText("Back", 225 - MeasureText("Back", 40) / 2, screenHeight -140, 40, WHITE);
        EndDrawing();
    }

    void handleInput() override {
        // Handle user input (e.g., button click to go to menu or restart)
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, exitButton)) {
            exitButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SceneManager::getInstance().changeScene("MENU");
            }
		}
        else exitButtonColor = GRAY;
    }

    std::string getSceneName() const override {
        return "HIGHSCORE";
    }
};
