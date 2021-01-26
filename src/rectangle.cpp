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

bool Rectangle::collidesRect( Rectangle& inputRectangle)
{
    return collidesLeftRight(inputRectangle) && collidesUpDown(inputRectangle);
}

bool Rectangle::collidesUpDown( Rectangle& inputRectangle)
{
    return this->getTopEdge() <= inputRectangle.getBottomEdge() &&
           this->getBottomEdge() >= inputRectangle.getTopEdge();
}

bool Rectangle::collidesLeftRight( Rectangle& inputRectangle)
{
    return this->getLeftEdge() <= inputRectangle.getRightEdge() &&
           this->getRightEdge() >= inputRectangle.getLeftEdge();
}

bool Rectangle::containsPoint(const Point& inputPoint)
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
Sint32 Rectangle::getTopEdge() 
{
    return this->getRectY();
}

Sint32 Rectangle::getBottomEdge() 
{
    return this->getRectY() + this->getRectH();
}

Sint32 Rectangle::getLeftEdge() 
{
    return this->getRectX();
}

Sint32 Rectangle::getRightEdge() 
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
Sint32 Rectangle::getRectX() {
    return this->rect.x;
}

Sint32 Rectangle::getRectY() {
    return this->rect.y;
}

Sint32 Rectangle::getRectW() {
    return this->rect.w;
}

Sint32 Rectangle::getRectH() {
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


Rectangle* Rectangle::getRectangle(){
    return this;
}

const SDL_Rect* Rectangle::getRect() const {
    const SDL_Rect * p_rect = &(this->rect);
    return p_rect;
}

Sint32 Rectangle::getLayer() const{
    return this->layer;
}

Uint32 Rectangle::getID() const{
    return this->id;
}

void Rectangle::setID(Uint32 input) {
    this->id = input;
}