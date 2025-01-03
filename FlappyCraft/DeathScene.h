#pragma once
#include "Scene.h"
#include "globals.h"
#include "raylib.h"

class DeathScene : public Scene {
public:
    Rectangle respawnButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2, 500, 60 };
    Rectangle titleScreenButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2 + 80, 500, 60 };

    Color respawnButtonColor = GRAY;
    Color titleScreenButtonColor = GRAY;

    void update() override {
    }

    void draw() override {
        BeginDrawing();
        ClearBackground(Color{ 224, 85, 85 });
        //Text
        DrawText("You Died!", screenWidth / 2 - 220, screenHeight / 3 - 100, 100, WHITE);
        DrawText(("Score: " + std::to_string(player.score)).c_str(), screenWidth / 2 - 75, screenHeight / 3, 40, WHITE);

        DrawRectangleRec(respawnButton, respawnButtonColor);
        DrawText("Respawn", screenWidth / 2 - MeasureText("Respawn", 40) / 2, screenHeight / 2 + 10, 40, WHITE);

        DrawRectangleRec(titleScreenButton, titleScreenButtonColor);
        DrawText("Title Screen", screenWidth / 2 - MeasureText("Title Screen", 40) / 2, screenHeight / 2 + 90, 40, WHITE);
        EndDrawing();
    }

    void handleInput() override {
        // Handle user input (e.g., button click to go to menu or restart)
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, respawnButton)) {
            respawnButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                player.health = player.maxHealth;
                player.xPos = player.xPosStart;
                player.yPos = player.yPosStart;
                player.healthImmunityTimer = 0;
                player.isDead = false;
                player.LeftHand = "EMPTY";
                player.RightHand = "EMPTY";
                player.LastUsedHand = "NONE";
                player.velocity = 0.0f;
                player.score = 0;
                map.reset();
                enemies.clear();
                enemies = map.getEnemies();
                SceneManager::getInstance().changeScene("GAME");
            }
        }
        else if (CheckCollisionPointRec(mousePos, titleScreenButton)) {
            titleScreenButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SceneManager::getInstance().changeScene("MENU");
            }
        }
        else {
			respawnButtonColor = GRAY;
			titleScreenButtonColor = GRAY;
        }
    }

    std::string getSceneName() const override {
        return "DEATH";
    }
};
