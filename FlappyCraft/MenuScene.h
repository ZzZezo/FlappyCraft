#pragma once
#include "Scene.h"
#include "globals.h"
#include "raylib.h"

class MenuScene : public Scene {
public:
    void update() override {
        // Handle any death-related logic
    }

    void draw() override {
        BeginDrawing();
            ClearBackground(BLUE);
        EndDrawing();
    }

    void handleInput() override {
        // Handle user input (e.g., button click to go to menu or restart)
    }

    std::string getSceneName() const override {
        return "MENU";
    }
};


