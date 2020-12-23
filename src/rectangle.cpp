#include <SDL2/SDL.h>

#include "Rectangle.hpp"

Rectangle::Rectangle(){
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.w = 0;
    this->rect.h = 0;
}

Rectangle::Rectangle(short x, short y, short w, short h)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
}

bool Rectangle::collidesRect(Rectangle *inputRectangle)
{
    return collidesLeftRight(inputRectangle) && collidesUpDown(inputRectangle);
}

bool Rectangle::collidesUpDown(Rectangle *inputRectangle)
{
    return this->getTopEdge() <= inputRectangle->getBottomEdge() &&
           this->getBottomEdge() >= inputRectangle->getTopEdge();
}

bool Rectangle::collidesLeftRight(Rectangle *inputRectangle)
{
    return this->getLeftEdge() <= inputRectangle->getRightEdge() &&
           this->getRightEdge() >= inputRectangle->getLeftEdge();
}

//EDGE getters
Uint16 Rectangle::getTopEdge()
{
    return this->getRectY();
}

Uint16 Rectangle::getBottomEdge()
{
    return this->getRectY() + this->getRectH();
}

Uint16 Rectangle::getLeftEdge()
{
    return this->getRectX();
}

Uint16 Rectangle::getRightEdge()
{
    return this->getRectX() + this->getRectW();
}


//X, Y, W, H setters
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

//X, Y, W, H getters
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
    return &(this->rect);
}