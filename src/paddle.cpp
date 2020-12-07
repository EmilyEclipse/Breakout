#include <SDL2/SDL.h>

#include "Paddle.hpp"


void Paddle::moveLeft(){
    int speed = calculateSpeed(this->movementFrameCount, this->maxMovementSpeed, this->acceleration);
    setRectX((getRect()->x) - speed);
    handleFrameCount();
}

void Paddle::moveRight(){
    int speed = calculateSpeed(this->movementFrameCount, this->maxMovementSpeed, this->acceleration);
    setRectX((getRect()->x) + speed);
    handleFrameCount();
}

void Paddle::setMoving(bool isMoving){
    this->moving = isMoving;
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