#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"
#include "Paddle.hpp"

class Ball: public Rectangle{
public:
    Ball(Uint16 *i_windowWidth, Uint16 *i_windowHeight, Paddle *i_paddle);
    void move();

private:
    void moveX();
    void moveY();

    bool onLeftEdge();
    bool onRightEdge();
    bool onTopEdge();
    bool onBottomEdge();

    void handleCollision();
    void calculateThetaForCollision();

    bool collidesWithPaddle();
    double getCenterPointFromLeftEdge();
    int16_t pixelOfPaddle();

    void calculateVectorMagnitude();
    void polarToXY();

    int8_t xSpeed;
    int8_t ySpeed;
    double angleLimitSansPI = 1 / 3.0;
    double magnitude;
    double theta;
    Uint16 *windowWidth, *windowHeight;
    Paddle *paddle;
};

#endif //BALL_HPP