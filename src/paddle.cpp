#include <SDL2/SDL.h>

#include "Paddle.hpp"
#include "Rectangle.hpp"
#include "RenderWindow.hpp"

Paddle::Paddle(Options& i_options)
    :   Rectangle(i_options.windowWidth / 2, 1000 * i_options.yScale,
                300 * i_options.xScale,
                50 * i_options.yScale,
                10,
                255, 255, 255
        ),
        leftLimit(0),
        rightLimit(i_options.windowWidth - getRectW()),
        options(i_options)
{ }

void Paddle::moveLeft(){
    int speed = calculateSpeed(this->movementFrameCount, this->maxMovementSpeed, this->acceleration);
    setRectX(getRectX() - speed);
    handleFrameCount();
}

void Paddle::moveRight(){
    int speed = calculateSpeed(this->movementFrameCount, this->maxMovementSpeed, this->acceleration);
    setRectX(getRectX() + speed);
    handleFrameCount();
}

void Paddle::setMoving(bool isMoving){
    this->moving = isMoving;
}

bool Paddle::canMoveLeft(){
    if(this->getRectX() <= leftLimit)
        return false;
    else
        return true;
}

bool Paddle::canMoveRight(){
    if(this->getRectX() >= rightLimit)
        return false;
    else
        return true;
}

double Paddle::getCenterPointFromLeftEdge(){
    return this->getRectX() + static_cast<double>(this->getRectW()) / 2;
}



short Paddle::calculateSpeed(short frameCount, short maxSpeed, short acceleration)
{
    short speed = (frameCount * acceleration + acceleration) * options.xScale;
    if (speed <= maxSpeed)
        return speed;
    else return maxSpeed;
}

void Paddle::handleFrameCount(){
    if(this->moving)
        ++this->movementFrameCount;
    else
        this->movementFrameCount = 0;
}