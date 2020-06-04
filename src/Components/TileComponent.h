#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include <SDL2/SDL.h>

#include "../../lib/glm/glm.hpp"

#include "../EntityManager.h"
#include "../AssetManager.h"

class TileComponent: public Component {
  public:
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    glm::vec2 position;

    TileComponent(int sourceX, int sourceY, int posX, int posY, int tileSize, int tileScale, std::string textureId) {
      this->texture = Game::assetManager->GetTexture(textureId);

      sourceRect.x = sourceX;
      sourceRect.y = sourceY;
      sourceRect.w = tileSize;
      sourceRect.h = tileSize;

      destRect.x = posX;
      destRect.y = posY;
      destRect.w = tileSize * tileScale;
      destRect.h = tileSize * tileScale;

      position.x = posX;
      position.y = posY;
    }

    ~TileComponent () {
      SDL_DestroyTexture(this->texture);
    }

    void Update (float dt) override {

    }

    void Render () override {
      TextureManager::Draw(
        this->texture,
        this->sourceRect,
        this->destRect,
        SDL_FLIP_NONE
      );
    }
  
};

#endif