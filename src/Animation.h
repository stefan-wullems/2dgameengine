#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
    unsigned int index;
    unsigned int animationSpeed;
    unsigned int frameAmount;
    Animation();
    Animation(unsigned int index, unsigned int animationSpeed, unsigned int frameAmount);
};

#endif