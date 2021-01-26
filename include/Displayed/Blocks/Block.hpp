#pragma once

#include <SDL2/SDL.h>

#include "Rectangle.hpp"

class Block: public Rectangle {
public:
    Block(Uint16 x, Uint16 y, Uint16 w, Uint16 h,
          Uint8 red, Uint8 green, Uint8 blue);
};