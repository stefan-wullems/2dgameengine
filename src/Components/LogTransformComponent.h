#ifndef LOG_TRANSFORM_COMPONENT_H
#define LOG_TRANSFORM_COMPONENT_H

#include <iostream>

#include "../EntityManager.h"

#include "./TransformComponent.h"
#include "./ColliderComponent.h"

class LogTransformComponent: public Component {
  public:
   
   

    void Initialize() override {
      
    }

    void Update(float dt) override {
      TransformComponent* transform = this->owner->GetComponent<TransformComponent>();
      ColliderComponent* collider = this->owner->GetComponent<ColliderComponent>();
      std::cout << this->owner->name << ":" << std::endl;
      std::cout << "\ttransform-x: " << transform->position.x << ", transform-y: " << transform->position.y << std::endl;
      std::cout << "\tcollider-x: " << collider->collider.x << ", collider-y: " << collider->collider.y << std::endl;
    }

    void Render() override {

    }
};

#endif