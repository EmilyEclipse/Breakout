#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"

class Paddle: public Rectangle
{
public:
    Paddle(Uint16 windowWidth);

    void moveLeft();
    void moveRight();
    void setMoving(bool isMoving);
    bool canMoveLeft();
    bool canMoveRight();
    double getCenterPointFromLeftEdge();
private:
    short maxMovementSpeed = 10;
    short acceleration = 2;
    short movementFrameCount = 0;
    bool moving = false;
    Uint16 leftLimit;
    Uint16 rightLimit;

    short calculateSpeed(short frameCount, short maxSpeed, short acceleration);
    void handleFrameCount();
};

#endif //PADDLE_HPP