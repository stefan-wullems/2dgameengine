#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <string>

#include "../Game.h"
#include "../EntityManager.h"
#include "../Colission.h"

#include "./TransformComponent.h"

class ColliderComponent: public Component {
  public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destRectangle;

    TransformComponent* transform;
    
    ColliderComponent(std::string tag, int x, int y, int w, int h) {
      this->colliderTag = tag;
      this->collider = {x,y,w,h};
    }

    void Initialize () override {
      if(this->owner->HasComponent<TransformComponent>()) {
        this->transform = owner->GetComponent<TransformComponent>();
        this->sourceRectangle = {0,0,this->transform->width, this->transform->height};
        this->destRectangle = {this->collider.x, this->collider.y, this->collider.w, this->collider.h};
      }
    }

    void Update (float dt) override {
      if(this->owner->HasComponent<TransformComponent>()) {
        this->collider.x = static_cast<int>(this->transform->position.x);
        this->collider.y = static_cast<int>(this->transform->position.y); 
        this->collider.w = this->transform->width * this->transform->scale;
        this->collider.h = this->transform->height * this->transform->scale;
      }
      this->destRectangle.x = this->collider.x - Game::camera.x;
      this->destRectangle.y = this->collider.y - Game::camera.y; 
    }
};

#endif