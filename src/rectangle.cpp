#include <SDL2/SDL.h>

#include "Rectangle.hpp"

Rectangle::Rectangle(short x, short y, short w, short h)
{
    (*this).rect.x = x;
    (*this).rect.y = y;
    (*this).rect.w = w;
    (*this).rect.h = h;
}

void Rectangle::setRectX(short value)
{
    this->rect.x = value;
}

void Rectangle::setRectY(short value)
{
    this->rect.y = value;
}

// void Rectangle::moveX(short moveX){
//     (*this).rect.x += moveX;
// }

// void Rectangle::moveY(short moveY){
//     (*this).rect.y += moveY;
// }

SDL_Rect* Rectangle::getRect()
{
    return &(*this).rect;
}