#include <iostream>

#include "../lib/glm/glm.hpp"

#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"

#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardInputComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/LogTransformComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Window* Game::window;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

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

Entity& player = manager.AddEntity("chopper", PLAYER_LAYER);
void Game::LoadLevel(int levelNum) {

  assetManager->AddTexture("tank-right-facing", std::string("./assets/images/tank-big-right.png").c_str());
  assetManager->AddTexture("tank-left-facing", std::string("./assets/images/tank-big-left.png").c_str());

  assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
  assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());

  assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

  map = new Map("jungle-tiletexture", 2, 32);
  map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

  int w,h; 
  SDL_GetWindowSize(window, &w, &h);

  Entity& topRight = manager.AddEntity("top-right", ENEMY_LAYER);
  topRight.AddComponent<TransformComponent>(0, 0, 100, 20, 30, 30, 1);
  topRight.AddComponent<SpriteComponent>("tank-right-facing");
  topRight.AddComponent<ColliderComponent>("enemy", 0, 0, 30, 30);
  
  Entity& topLeft = manager.AddEntity("top-left", ENEMY_LAYER);
  topLeft.AddComponent<TransformComponent>(w - 30, 0, -100, 20, 30, 30, 1);
  topLeft.AddComponent<SpriteComponent>("tank-left-facing");
  topLeft.AddComponent<ColliderComponent>("enemy", w - 30, 0, 30, 30);
  
  Entity& bottomLeft = manager.AddEntity("bottom-left", ENEMY_LAYER);
  bottomLeft.AddComponent<TransformComponent>(w - 30, h - 30, -100, -20, 30, 30, 1);
  bottomLeft.AddComponent<SpriteComponent>("tank-left-facing");
  bottomLeft.AddComponent<ColliderComponent>("enemy", w - 30, h - 30, 30, 30);
  
  Entity& bottomRight = manager.AddEntity("bottom-right", ENEMY_LAYER);
  bottomRight.AddComponent<TransformComponent>(0, h - 30, 100, -20, 30, 30, 1);
  bottomRight.AddComponent<SpriteComponent>("tank-right-facing");
  bottomRight.AddComponent<ColliderComponent>("enemy", 0, h - 30, 30, 30);

  player.AddComponent<TransformComponent>(320, 106, 0, 0, 32, 32, 1);
  player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
  player.AddComponent<KeyboardInputComponent>("w", "d", "s", "a", "space");
  player.AddComponent<ColliderComponent>("player", 320, 106, 32, 32);

  Entity& radar = manager.AddEntity("radar", GUI_LAYER);
  radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  radar.AddComponent<SpriteComponent>("radar-image", 8, 200, false, true);
}

void Game::ProcessInput() {
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

  this->HandleCameraMovement();
  this->CheckColissions();
}

void Game::HandleCameraMovement() {
  TransformComponent* tranform = player.GetComponent<TransformComponent>();

  Game::camera.x = tranform->position.x - (WINDOW_WIDTH / 2);
  Game::camera.y = tranform->position.y - (WINDOW_HEIGHT / 2);

  Game::camera.x = Game::camera.x < 0 ? 0 : Game::camera.x;
  Game::camera.y = Game::camera.y < 0 ? 0 : Game::camera.y;
  Game::camera.x = Game::camera.x > camera.w ? Game::camera.w : Game::camera.x;
  Game::camera.y = Game::camera.y > camera.h ? Game::camera.h : Game::camera.y;
}

void Game::CheckColissions() {
  std::string collidedTag =  manager.CheckEntityColissions(player);
  if(collidedTag.compare("enemy") == 0) {
    std::cout << "bla" << std::endl;
    this->isRunning = false;
  }
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