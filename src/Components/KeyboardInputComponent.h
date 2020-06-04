#ifndef KEYBOARD_INPUT_COMPONENT_H
#define KEYBOARD_INPUT_COMPONENT_H

#include <map>
#include <string>

#include "../Game.h"
#include "../EntityManager.h"

#include "./TransformComponent.h"
#include "./SpriteComponent.h"

inline std::string GetSDLKeyStringCode(std::string key) {
  if(key.compare("up") == 0) return "1073741906";
  if(key.compare("down") == 0) return "1073741905";
  if(key.compare("left") == 0) return "1073741904";
  if(key.compare("right") == 0) return "1073741904";
  if(key.compare("space") == 0) return "32";
  return std::to_string(static_cast<int>(key[0]));
}

class KeyboardInputComponent: public Component {
  
  public:
    std::string upKey;
    std::string rightKey;
    std::string downKey;
    std::string leftKey;
    std::string shootKey;

    TransformComponent* transform;
    SpriteComponent* sprite;

    KeyboardInputComponent() {}

    KeyboardInputComponent(
      std::string up, 
      std::string right, 
      std::string down, 
      std::string left,
      std::string shoot
    ) {
      this->upKey = GetSDLKeyStringCode(up);
      this->rightKey = GetSDLKeyStringCode(right);
      this->downKey = GetSDLKeyStringCode(down);
      this->leftKey = GetSDLKeyStringCode(left);
      this->shootKey = GetSDLKeyStringCode(shoot);
    }
    
    void Initialize() override {
      this->transform = owner->GetComponent<TransformComponent>();
      this->sprite = owner->GetComponent<SpriteComponent>();
    }

    void Update(float dt) override {
      if(Game::event.type == SDL_KEYDOWN) {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);

        if(keyCode.compare(this->upKey) == 0) {
          this->transform->velocity.y = -50;
          this->transform->velocity.x = 0;

          this->sprite->Play("UpAnimation");
        }
        if(keyCode.compare(this->rightKey) == 0) {
          this->transform->velocity.y = 0;
          this->transform->velocity.x = 50;

          this->sprite->Play("RightAnimation");
        }
        if(keyCode.compare(this->downKey) == 0) {
          this->transform->velocity.y = 50;
          this->transform->velocity.x = 0;

          this->sprite->Play("DownAnimation");
        }
        if(keyCode.compare(this->leftKey) == 0) {
          this->transform->velocity.y = 0;
          this->transform->velocity.x = -50;

          this->sprite->Play("LeftAnimation");
        }
      }

      if(Game::event.type == SDL_KEYUP) {
        std::string keyCode = std::to_string(Game::event.key.keysym.sym);

        if(keyCode.compare(this->upKey) == 0) {
          this->transform->velocity.y = 0;
        }
        if(keyCode.compare(this->rightKey) == 0) {
          this->transform->velocity.x = 0;
        }
        if(keyCode.compare(this->downKey) == 0) {
          this->transform->velocity.y = 0;
        }
        if(keyCode.compare(this->leftKey) == 0) {
          this->transform->velocity.x = 0;
        }
      }
    }

    void Render () override {}
};

#endif