#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"

class AssetManager;

class Game {
  private:
    bool isRunning;

  public:
    Game();
    ~Game();
    int ticksLastFrame;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    static AssetManager* assetManager;
    static SDL_Window* window;
    static SDL_Event event;
    static SDL_Rect camera;
    void HandleCameraMovement();
    void LoadLevel(int levelNumber);
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void CheckColissions();
};

#endif