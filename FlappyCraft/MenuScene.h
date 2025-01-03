#pragma once
#include "Scene.h"
#include "globals.h"
#include "raylib.h"
#include <fstream>
#include <random>

class MenuScene : public Scene {
public:

    Rectangle playButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2-20, 500, 60 };
    Rectangle highscoreButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2-20 + 80, 500, 60 };
    Rectangle userButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2-20 + 160, 500, 60 };
    Rectangle exitButton = { (float)screenWidth / 2 - 250, (float)screenHeight / 2-20 + 240, 500, 60 };
    Color playButtonColor = GRAY;
	Color highscoreButtonColor = GRAY;
    Color userButtonColor = GRAY;
	Color exitButtonColor = GRAY;
    Texture2D titleTexture = LoadTexture("assets/menu/title.png");
    Image backgroundImage = LoadImage("assets/menu/background.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);

    std::string splashtext;

    MenuScene() {
        generateSplashText();
    }

    void update() override {
        
    }

    void draw() override {
        BeginDrawing();
            DrawTexture(backgroundTexture, 0, 0, WHITE);

			DrawTexture(titleTexture, screenWidth / 2 - titleTexture.width / 2, screenHeight/3-titleTexture.height, WHITE);

            DrawRectangleRec(playButton, playButtonColor);
            DrawText("Play!", screenWidth / 2 - MeasureText("Play!", 40) / 2, screenHeight / 2-10, 40, WHITE);

            DrawRectangleRec(highscoreButton, highscoreButtonColor);
            DrawText("Rankings", screenWidth / 2 - MeasureText("Rankings", 40) / 2, screenHeight / 2 -10 + 80, 40, WHITE);

            DrawRectangleRec(userButton, userButtonColor);
            DrawText("Switch User", screenWidth / 2 - MeasureText("Switch User", 40) / 2, screenHeight / 2 - 10 + 160, 40, WHITE);

            DrawRectangleRec(exitButton, exitButtonColor);
            DrawText("Quit Game", screenWidth / 2 - MeasureText("Quit Game", 40) / 2, screenHeight / 2 -10 + 240, 40, WHITE);

            //"Splash" Text
            DrawTextPro(GetFontDefault(), splashtext.c_str(), Vector2{1300.0f-MeasureText(splashtext.c_str(), 35) / 2,300.0f+MeasureText(splashtext.c_str(), 35)/5  }, Vector2{0,0}, -25.0f, 35, 2.0f, YELLOW);
        EndDrawing();
    }

    void handleInput() override {
        // Handle user input (e.g., button click to go to menu or restart)
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, playButton)) {
            playButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                generateSplashText();
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
        else if (CheckCollisionPointRec(mousePos, highscoreButton)) {
            highscoreButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                generateSplashText();
                SceneManager::getInstance().changeScene("HIGHSCORE");
            }
        }
        else if (CheckCollisionPointRec(mousePos, userButton)) {
            userButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                generateSplashText();
                SceneManager::getInstance().changeScene("USER");
            }
        }
        else if (CheckCollisionPointRec(mousePos, exitButton)) {
            exitButtonColor = DARKGRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                exit(0);
            }
        }
        else {
            playButtonColor = GRAY;
            highscoreButtonColor = GRAY;
			userButtonColor = GRAY;
            exitButtonColor = GRAY;
        }
    }

    std::string getSceneName() const override {
        return "MENU";
    }

    void generateSplashText() {
        splashtext = "Lorem ipsum";
        std::ifstream file("assets/menu/splashes.txt");
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        std::srand(std::time(0)); // Seed for randomness
        splashtext = lines[std::rand() % lines.size()];
    }
};


