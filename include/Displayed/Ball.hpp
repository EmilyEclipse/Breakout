#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

#include "AudioManager.hpp"
#include "Rectangle.hpp"
#include "HyperBlock.hpp"
#include "Geometry.hpp"
#include "Paddle.hpp"
#include "ScoreKeeper.hpp"

class Ball: public Rectangle{
public:
    Ball(Uint16 *i_windowWidth, Uint16 *i_windowHeight, Paddle *i_paddle,
            HyperBlock *i_hyper, ScoreKeeper* i_SK, AudioManager* i_AM);
    void move();

private:
    void moveX();
    void moveY();

    bool onLeftEdge();
    bool onRightEdge();
    bool onTopEdge();
    bool onBottomEdge();

    void handlePaddleCollision();
    void calculateThetaForCollision();

    bool collidesWithPaddle();
    double getCenterPointFromLeftEdge();
    int16_t pixelOfPaddle();

    void polarToXY();  
    void teleportBallByCorner(Uint8 cornerIndex, Uint16 x, Uint16 y);
    void thetaFromXY();

    void handleScreenCollison();
    void handleBlockCollision();

    double xSpeed;
    double ySpeed;
    const double angleLimitSansPI = static_cast<double>(1) / 3;
    double magnitude;
    double theta;
    Uint16 *windowWidth, *windowHeight;
    Paddle *paddle;
    HyperBlock *hyper;
    ScoreKeeper* scoreKeeper;
    AudioManager* audioManager;
};

#endif //BALL_HPP