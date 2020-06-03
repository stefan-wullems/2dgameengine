#include <iostream>

#include "../lib/glm/glm.hpp"

#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"

#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {
  this->isRunning = false;
}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL." << std::endl;
    return;
  }

  window = SDL_CreateWindow(
    NULL, 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    width, 
    height,
    SDL_WINDOW_BORDERLESS
  );

  if(!window) {
    std::cerr << "Error creating SDL window." << std::endl;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);

  if(!renderer) {
    std::cerr << "Error creating renderer." << std::endl;
  }
  ticksLastFrame = 0;

  LoadLevel(0);

  manager.PrintEntities();

  isRunning = true;
  return;
}

void Game::LoadLevel(int levelNum) {

  assetManager->AddTexture("tank-right-facing", ((std::string)"./assets/images/tank-big-right.png").c_str());
  assetManager->AddTexture("tank-left-facing", ((std::string)"./assets/images/tank-big-left.png").c_str());

  int w,h; 
  SDL_GetWindowSize(window, &w, &h);

  Entity& topRight = manager.AddEntity("top-right");
  topRight.AddComponent<TransformComponent>(0, 0, 100, 20, 30, 30, 1);
  topRight.AddComponent<SpriteComponent>("tank-right-facing");
  
  Entity& topLeft = manager.AddEntity("top-left");
  topLeft.AddComponent<TransformComponent>(w - 30, 0, -100, 20, 30, 30, 1);
  topLeft.AddComponent<SpriteComponent>("tank-left-facing");
  
  Entity& bottomLeft = manager.AddEntity("bottom-left");
  bottomLeft.AddComponent<TransformComponent>(w - 30, h - 30, -100, -20, 30, 30, 1);
  bottomLeft.AddComponent<SpriteComponent>("tank-left-facing");
  
  Entity& bottomRight = manager.AddEntity("bottom-right");
  bottomRight.AddComponent<TransformComponent>(0, h - 30, 100, -20, 30, 30, 1);
  bottomRight.AddComponent<SpriteComponent>("tank-right-facing");

}

void Game::ProcessInput() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {
  int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

  if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
    SDL_Delay(timeToWait);
  }

  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  float dt = (SDL_GetTicks() - ticksLastFrame) / 1000.f;
  dt = dt > FRAME_TARGET_TIME ? FRAME_TARGET_TIME : dt;

  ticksLastFrame = SDL_GetTicks();

  manager.Update(dt);
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
  SDL_RenderClear(renderer);

  if(manager.HasNoEntities()) return;
  else {
    manager.Render();

    SDL_RenderPresent(renderer);
  }  
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}