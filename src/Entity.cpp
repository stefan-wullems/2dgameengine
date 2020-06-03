#include <iostream>
#include <cxxabi.h>
#define quote(x) #x

#include "./Entity.h"

Entity::Entity(EntityManager& manager): manager(manager) {
  this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name) {
  this->isActive = true;
}

void Entity::Update(float dt) {
  for(auto& component: components) {
    component->Update(dt);
  }
}

void Entity::Render() {
  for(auto& component: components) {
    component->Render();
  }
}

void Entity::Destroy() {
  this->isActive = false;
}

void Entity::PrintComponents() const {
  for(auto& component: componentTypeMap) {
    std::cout << "  Component<" << component.first->name() << ">" << std::endl;
  }
}

bool Entity::IsActive() const {
  return this->isActive;
}