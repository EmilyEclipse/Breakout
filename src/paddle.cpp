#include <SDL2/SDL.h>

#include "Paddle.hpp"
#include "Rectangle.hpp"
#include "RenderWindow.hpp"

Paddle::Paddle(Uint16 windowWidth) : Rectangle(windowWidth / 2, 1000, 300, 50){
    this->leftLimit = 0;
    this->rightLimit = windowWidth - getRectW();
}

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



short Paddle::calculateSpeed(short frameCount, short maxSpeed, short acceleration)
{
    short speed = frameCount * acceleration + acceleration;
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