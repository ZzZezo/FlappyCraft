#pragma once
#include <string>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update() = 0;      // Called every frame to update the scene's logic
    virtual void draw() = 0;        // Called every frame to draw the scene
    virtual void handleInput() = 0; // Handle user input for scene transitions
    virtual std::string getSceneName() const = 0; // Return scene name for easy identification
};
