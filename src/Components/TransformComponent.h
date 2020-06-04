#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <iostream>
#include <SDL2/SDL.h>

#include "../../lib/glm/glm.hpp"

#include "../EntityManager.h"
#include "../Game.h"

class TransformComponent: public Component {
  public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
      position = glm::vec2(posX, posY);
      velocity = glm::vec2(velX, velY);
      width = w;
      height = h;
      scale = s;
    }

    void Initialize() override {
      
    }

    void Update(float dt) override {
      int windowWidth,windowHeight; 
      SDL_GetWindowSize(Game::window, &windowWidth, &windowHeight);

      float newX = position.x + (velocity.x * dt);
      float newY = position.y + (velocity.y * dt);

      if (newX > 0 && newX < windowWidth - this->width) this->position.x = newX;
      if (newY > 0 && newY < windowHeight - this->height) this->position.y = newY;
    }

    void Render() override {
    }
};

#endif