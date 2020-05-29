#include "./EntityManager.h"

void EntityManager::ClearData() {
  for(auto& entity: entities) {
    entity->Destroy();
  }
}

bool EntityManager::HasNoEntities() {
  return this->entities.size() == 0;
}

void EntityManager::Update(float dt) {
  for(auto& entity: entities) {
    entity->Update(dt);
  }
}

void EntityManager::Render() {
  for(auto& entity: entities) {
    entity->Render();
  }
}

Entity& EntityManager::AddEntity (std::string entityName) {
  Entity *entity = new Entity(*this, entityName);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
  return entities;
}

unsigned int EntityManager::GetEntityCount() const {
  return entities.size();
}

