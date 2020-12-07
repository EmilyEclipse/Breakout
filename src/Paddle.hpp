#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"

class Paddle: public Rectangle
{
    using Rectangle::Rectangle; //use the Rectangle class's constructor
public:
    void moveLeft();
    void moveRight();
    void setMoving(bool isMoving);
private:
    short maxMovementSpeed = 10;
    short acceleration = 2;
    short movementFrameCount = 0;
    bool moving = false;

    short calculateSpeed(short frameCount, short maxSpeed, short acceleration);
    void handleFrameCount();
};

#endif //PADDLE_HPP