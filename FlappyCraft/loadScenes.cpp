#include "loadScenes.h"

SceneManager& sceneManager = SceneManager::getInstance();

void loadScenes() {
	GameScene gameScene;
	DeathScene deathScene;
	MenuScene menuScene;
	UserScene userScene;
	HighscoreScene highscoreScene;

	sceneManager.addScene(make_unique<GameScene>(gameScene));
	sceneManager.addScene(make_unique<DeathScene>(deathScene));
	sceneManager.addScene(make_unique<MenuScene>(menuScene));
	sceneManager.addScene(make_unique<UserScene>(userScene));
	sceneManager.addScene(make_unique<HighscoreScene>(highscoreScene));

	// Start with the game scene
	sceneManager.changeScene("MENU");
}