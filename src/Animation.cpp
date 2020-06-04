#include <iostream>
#include "./Animation.h"

Animation::Animation() {

}

Animation::Animation(unsigned int index, unsigned int animationSpeed, unsigned int frameAmount) {
  this->index = index;
  this->animationSpeed = animationSpeed;
  this->frameAmount = frameAmount;
}