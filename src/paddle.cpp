#include <SDL2/SDL.h>

#include "Displayed/Paddle.hpp"
#include "Displayed/Blocks/HyperBlock.hpp"
#include "Rectangle.hpp"
#include "RenderWindow.hpp"

Paddle::Paddle(const Options& i_options, const HyperBlock& i_hyper)
    :   Rectangle(i_options.windowWidth / 2, 1000 * i_options.yScale,
                300 * i_options.xScale,
                50 * i_options.yScale,
                10,
                255, 255, 255
        ),
        leftLimit(0),
        rightLimit(i_options.windowWidth - getRectW()),
        options(i_options),
        hyper(i_hyper)
{}

void Paddle::moveLeft(){
    int speed = this->getMaxSpeed();//calculateSpeed(this->movementFrameCount, 100, this->getMaxSpeed(), this->acceleration);
    setRectX(getRectX() - speed);
    handleFrameCount();
}

void Paddle::moveRight(){
    int speed = this->getMaxSpeed();//calculateSpeed(this->movementFrameCount, 100, this->getMaxSpeed(), this->acceleration);
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



short Paddle::calculateSpeed(short frameCount, short msToMax, short maxSpeed, short acceleration)
{
    short framesToMax = msToMax * options.framesPerSecond / 1000;
    if(frameCount >= framesToMax)
    {
        return maxSpeed;
    } else {
        //f(x) = ax^2 + bx + c
        double a = -0.05;
        double b = -2 * framesToMax * a;
        return a * framesToMax * framesToMax + b * framesToMax;
    }
    // short speed = (frameCount * acceleration + acceleration) * options.xScale;
    // if (speed <= maxSpeed)
    //     return speed;
    // else return maxSpeed;
}

void Paddle::handleFrameCount(){
    if(this->moving)
        ++this->movementFrameCount;
    else
        this->movementFrameCount = 0;
}

short Paddle::getMaxSpeed() const{
    return this->maxMovementSpeed * (1 + 0.1 * hyper.getHighestCollidedRow());
}