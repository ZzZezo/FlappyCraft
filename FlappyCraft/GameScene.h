#pragma once
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "globals.h"
#include "gui.h"

class GameScene : public Scene {
private:
    Camera2D camera;

public:
    GameScene() : camera(Camera2D()) 
    {
        camera = { 0 };
        camera.target = { player.xPos + player.xScale / 2, player.yPos + player.yScale / 2 };
        camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
        camera.zoom = 1.0f;

        player.loadPlayerTexture();
        map.loadMapTextures();
        map.reset();

        enemies = map.getEnemies();
    }

    void update() override {
        player.updatePlayer(map, enemies, username);
        camera.target = { player.xPos + player.xScale / 2, player.yPos + player.yScale / 2 };
        // Update enemies, and other game logic
        vector<Enemy*> newEnemies;
        for (Enemy*& enemy : enemies) {
            enemy->update(enemies, newEnemies);
        }
        enemies.insert(enemies.end(), newEnemies.begin(), newEnemies.end());
    }

    void draw() override {
        BeginDrawing();
            BeginMode2D(camera);
                ClearBackground(SKYBLUE);
                map.drawMap();
                map.drawItems();
                for (Enemy*& enemy : enemies) enemy->draw();
                DrawTexture(player.playerTexture, player.xPos, player.yPos, player.pColor);
                EndMode2D();
                drawGUI(screenWidth, screenHeight, player);
            DrawItems(player.LeftHand, player.RightHand);
        EndDrawing();
    }

    void handleInput() override {
        // Handle player input (e.g., for pausing or dying)
        if (player.isDead) {
            // Transition to death screen when player dies
            SceneManager::getInstance().changeScene("DEATH");
        }
    }

    std::string getSceneName() const override {
        return "GAME";
    }
};