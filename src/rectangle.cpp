#include <SDL2/SDL.h>

#include "Rectangle.hpp"

Rectangle::Rectangle(short x, short y, short w, short h)
{
    (*this).rect.x = x;
    (*this).rect.y = y;
    (*this).rect.w = w;
    (*this).rect.h = h;
}

SDL_Rect* Rectangle::getRect()
{
    return &(*this).rect;
}