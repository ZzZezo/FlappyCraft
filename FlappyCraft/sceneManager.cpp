#include "SceneManager.h"

std::string currentScene = "GAME"; // Definition der globalen Variable

void changeScene(const std::string& scene) {
    currentScene = scene;
}