#include <iostream>
#include "./EntityManager.h"
#include "./Colission.h"
#include "./Components/ColliderComponent.h"

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
  for (int layerNumber = 0; layerNumber <= LAYER_AMOUNT; layerNumber++) {
    for(auto& entity: this->GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
      entity->Render();
    }
  }
}

std::string EntityManager::CheckEntityColissions(Entity& myEntity) {
  ColliderComponent* myCollider = myEntity.GetComponent<ColliderComponent>();
  for(auto& entity: entities) {
    if(entity->name.compare(myEntity.name) != 0 && entity->name.compare("tile") != 0)
      if(entity->HasComponent<ColliderComponent>()) {
        ColliderComponent* entityCollider = entity->GetComponent<ColliderComponent>();
        if(Colission::IsColliding(entityCollider->collider, myCollider->collider)) {
          return entityCollider->colliderTag;
        }
      }
  }

  return std::string();
}

void EntityManager::PrintEntities() const {
  for(auto& entity: entities) {
    std::cout << std::endl;
    std::cout << "Entity name: " << entity->name << std::endl;
    entity->PrintComponents();
  }
}

Entity& EntityManager::AddEntity (std::string entityName, LayerType layer) {
  Entity *entity = new Entity(*this, entityName, layer);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
  return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
  std::vector<Entity*> layerEntities;
  for(auto &entity: entities) {
    if(entity->layer == layer) {
      layerEntities.emplace_back(entity);
    }
  }
  return layerEntities;
}

unsigned int EntityManager::GetEntityCount() const {
  return entities.size();
}


