#ifndef COLISSION_H
#define COLISSION_H

#include <SDL2/SDL.h>

class Colission {
  public:
    static bool IsColliding(const SDL_Rect& a, const SDL_Rect& b);
};

#endif