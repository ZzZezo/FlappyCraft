#pragma once
#include <memory>
#include <unordered_map>
#include "Scene.h"

class SceneManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* currentScene;

    SceneManager() : currentScene(nullptr) {}

public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    void addScene(std::unique_ptr<Scene> scene) {
        scenes[scene->getSceneName()] = std::move(scene);
    }

    void changeScene(const std::string& sceneName) {
        if (scenes.find(sceneName) != scenes.end()) {
            currentScene = scenes[sceneName].get();
        }
    }

    void update() {
        if (currentScene) {
            currentScene->handleInput();
            currentScene->update();
        }
    }

    void draw() {
        if (currentScene) {
            currentScene->draw();
        }
    }
};