#include <SDL2/SDL.h>

#include <algorithm>

#include "Rectangle.hpp"

Rectangle::Rectangle()
{
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

Rectangle::Rectangle(short x, short y, short w, short h, Sint16 i_layer,
                    Uint8 i_red, Uint8 i_green, Uint8 i_blue)
: layer(i_layer), red(i_red), green(i_green), blue(i_blue)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
}

Rectangle::Rectangle(Point first, Point second)
{
    Uint32 absDiffX = abs(first.x - second.x);
    Uint32 absDiffY = abs(first.y - second.y);
    Sint32 rectX = std::min(first.x, second.x); //- absDiffX;
    Sint32 rectY = std::min(first.y, second.y); //- absDiffY;

    this->rect.x = rectX;
    this->rect.y = rectY;
    this->rect.w = absDiffX;
    this->rect.h = absDiffY;
}

bool Rectangle::collidesRect(const Rectangle& inputRectangle) const
{
    return collidesLeftRight(inputRectangle) && collidesUpDown(inputRectangle);
}

bool Rectangle::collidesUpDown(const Rectangle& inputRectangle) const
{
    return this->getTopEdge() <= inputRectangle.getBottomEdge() &&
           this->getBottomEdge() >= inputRectangle.getTopEdge();
}

bool Rectangle::collidesLeftRight(const Rectangle& inputRectangle) const
{
    return this->getLeftEdge() <= inputRectangle.getRightEdge() &&
           this->getRightEdge() >= inputRectangle.getLeftEdge();
}

bool Rectangle::containsPoint(const Point& inputPoint) const
{
    return  this->getLeftEdge() <= inputPoint.x &&
            this->getRightEdge() >= inputPoint.x &&
            this->getTopEdge() <= inputPoint.y &&
            this->getBottomEdge() >= inputPoint.y;
}



Line Rectangle::getTopLine() 
{
    return Line(getTLPoint(), getTRPoint());
}

Line Rectangle::getBottomLine() 
{
    return Line(getBLPoint(), getBRPoint());
}

Line Rectangle::getLeftLine() 
{
    return Line(getTLPoint(), getBLPoint());
}

Line Rectangle::getRightLine() 
{
    return Line(getTRPoint(), getBRPoint());
}

//EDGE getters
Sint32 Rectangle::getTopEdge() const
{
    return this->getRectY();
}

Sint32 Rectangle::getBottomEdge() const
{
    return this->getRectY() + this->getRectH();
}

Sint32 Rectangle::getLeftEdge() const
{
    return this->getRectX();
}

Sint32 Rectangle::getRightEdge() const
{
    return this->getRectX() + this->getRectW();
}

//CORNER getters
Point Rectangle::getTLPoint() {
    return Point(this->getRectX(), this->getRectY());
}

Point Rectangle::getTRPoint() {
    return Point(this->getRectX() + this->getRectW(), this->getRectY());
}

Point Rectangle::getBLPoint() {
    return Point(this->getRectX(), this->getRectY() + this->getRectH());
}

Point Rectangle::getBRPoint() {
    return Point(this->getRectX() + this->getRectW(),
                    this->getRectY() + this->getRectH());
}

//X, Y, W, H setters
void Rectangle::setRectX(Sint32 value)
{
    this->rect.x = value;
}

void Rectangle::setRectY(Sint32 value)
{
    this->rect.y = value;
}

void Rectangle::setRectW(Sint32 value){
    this->rect.w = value;
}

void Rectangle::setRectH(Sint32 value){
    this->rect.h = value;
}

//X, Y, W, H getters
Sint32 Rectangle::getRectX() const
{
    return this->rect.x;
}

Sint32 Rectangle::getRectY() const
{
    return this->rect.y;
}

Sint32 Rectangle::getRectW() const
{
    return this->rect.w;
}

Sint32 Rectangle::getRectH() const
{
    return this->rect.h;
}

Uint8 Rectangle::getRed() const{
    return this->red;
}

Uint8 Rectangle::getGreen() const{
    return this->green;
}

Uint8 Rectangle::getBlue() const{
    return this->blue;
}

const Rectangle* Rectangle::getRectangle() const{
    const Rectangle* rect_p = this;
    return rect_p;
}

const SDL_Rect* Rectangle::getRect() const {
    const SDL_Rect* p_rect = &(this->rect);
    return p_rect;
}

Sint32 Rectangle::getLayer() const{
    return this->layer;
}