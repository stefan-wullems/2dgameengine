#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "../TextureManager.h"
#include "../AssetManager.h"

#include "./TransformComponent.h"
#include "../Animation.h"

class SpriteComponent: public Component {
  private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;

    bool isFixed;
    bool isAnimated;
    int frameAmount;
    int animationSpeed;
    int animationIndex;

  public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent(const char* id) {
      this->isAnimated = false;
      this->SetTexture(id);
    }

    SpriteComponent(
      const char* id, 
      int frameAmount, 
      int animationSpeed, 
      bool hasDirections, 
      bool isFixed
    ): frameAmount(frameAmount), animationSpeed(animationSpeed), isFixed(isFixed) {
      this->isAnimated = true;

      std::cout << std::to_string(this->frameAmount) << std::endl;
      std::cout << std::to_string(this->animationIndex) << std::endl;
      std::cout << std::to_string(this->animationSpeed) << std::endl;
      std::cout << this->currentAnimationName << std::endl;

      if(hasDirections) {   
        this->animations.emplace("DownAnimation", Animation(0, this->animationSpeed, this->frameAmount));
        this->animations.emplace("RightAnimation", Animation(1, this->animationSpeed, this->frameAmount));
        this->animations.emplace("LeftAnimation", Animation(2, this->animationSpeed, this->frameAmount));
        this->animations.emplace("UpAnimation", Animation(3, this->animationSpeed, this->frameAmount));

        this->animationIndex = 0;
        this->currentAnimationName = "DownAnimation";
      } else {
        this->animations.emplace("SingleAnimation", Animation(0, this->animationSpeed, this->frameAmount));

        this->animationIndex = 0;
        this->currentAnimationName = "SingleAnimation";
      }

      this->Play(currentAnimationName);
      this->SetTexture(id);
    }

    void Play(std::string animationName) {
      this->frameAmount = this->animations[animationName].frameAmount;
      this->animationIndex = this->animations[animationName].index;
      this->animationSpeed = this->animations[animationName].animationSpeed;
      this->currentAnimationName = animationName;
    }

    void SetTexture(std::string assetTextureId) {
      this->texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Initialize() override {
      this->transform = owner->GetComponent<TransformComponent>();
      this->sourceRectangle.x = 0;
      this->sourceRectangle.y = 0;
      this->sourceRectangle.w = transform->width;
      this->sourceRectangle.h = transform->height;
    }

    void Update(float deltaTime) override {
      if(this->isAnimated) {
        this->sourceRectangle.x = this->sourceRectangle.w * static_cast<int>(((SDL_GetTicks() / this->animationSpeed) % this->frameAmount));
      }
      this->sourceRectangle.y = this->animationIndex * this->transform->height;

      this->destinationRectangle.x = static_cast<int>(this->transform->position.x);
      this->destinationRectangle.y = static_cast<int>(this->transform->position.y); 
      this->destinationRectangle.w = this->transform->width * this->transform->scale;
      this->destinationRectangle.h = this->transform->height * this->transform->scale;
    }

    void Render() override {
      TextureManager::Draw(this->texture, this->sourceRectangle, this->destinationRectangle, this->spriteFlip);
    }
};

#endif