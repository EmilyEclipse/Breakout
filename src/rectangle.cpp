#include <SDL2/SDL.h>

#include "Rectangle.hpp"

Rectangle::Rectangle(short x, short y, short w, short h)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
}

void Rectangle::setRectX(short value)
{
    this->rect.x = value;
}

void Rectangle::setRectY(short value)
{
    this->rect.y = value;
}

void Rectangle::setRectW(short value){
    this->rect.w = value;
}

void Rectangle::setRectH(short value){
    this->rect.h = value;
}


short Rectangle::getRectX(){
    return this->rect.x;
}

short Rectangle::getRectY(){
    return this->rect.y;
}

short Rectangle::getRectW(){
    return this->rect.w;
}

short Rectangle::getRectH(){
    return this->rect.h;
}

SDL_Rect* Rectangle::getRect()
{
    return &(*this).rect;
}