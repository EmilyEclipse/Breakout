#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>

#include "Displayed/Blocks/HyperBlock.hpp"
#include "Rectangle.hpp"
#include "Options.hpp"

class Paddle: public Rectangle
{
public:
    Paddle(const Options& i_options, const HyperBlock& i_hyper);

    void moveLeft();
    void moveRight();
    void setMoving(const bool isMoving);
    bool canMoveLeft();
    bool canMoveRight();
    double getCenterPointFromLeftEdge();
    short getMaxSpeed() const;
private:
    short maxMovementSpeed = 10;
    short acceleration = 2;
    short movementFrameCount = 0;
    bool moving = false;
    Uint16 leftLimit;
    Uint16 rightLimit;
    const Options& options;
    const HyperBlock& hyper;

    short calculateSpeed(short frameCount, short msToMax, short maxSpeed, short acceleration);
    void handleFrameCount();
};

#endif //PADDLE_HPP