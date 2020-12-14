#include <SDL2/SDL.h>

#include "Ball.hpp"
#include "Rectangle.hpp"
#include "Paddle.hpp"


Ball::Ball(Uint16 *i_windowWidth, Uint16 *i_windowHeight, Paddle *i_paddle) 
            : Rectangle(*i_windowWidth / 2, *i_windowHeight / 2, 50, 50){
    xSpeed = 7;
    ySpeed = 7;
    magnitude = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
    windowWidth = i_windowWidth;
    windowHeight = i_windowHeight;
    paddle = i_paddle;
}

void Ball::move(){
    if(onRightEdge() || onLeftEdge()){
        xSpeed *= -1;
    }
    if(onTopEdge() || onBottomEdge()){
        ySpeed *= -1;
    }
    if(this->collidesWithPaddle())
        handleCollision();
    moveX();
    moveY();
}

void Ball::moveX(){
    setRectX(getRectX() + xSpeed);
}

void Ball::moveY(){
    setRectY(getRectY() + ySpeed);
}

bool Ball::onRightEdge(){
    return getRectX() + getRectW() >= *windowWidth;
}

bool Ball::onLeftEdge(){
    return getRectX() <= 0;
}

bool Ball::onTopEdge(){
    return getRectY() <= 0;
}

bool Ball::onBottomEdge(){
    return getRectY() + getRectH() >= *windowHeight;
}


void Ball::handleCollision(){
    //Number of exit angles is 'paddle_width', plus another one for the paddle's center pixel
    //if the position of that pixel is an integer (otherwise it's just imaginary)
    calculateThetaForCollision();
    polarToXY();
}

void Ball::calculateThetaForCollision(){

    if(pixelOfPaddle() == 0){
        theta = M_PI_2;
    } else if(abs(pixelOfPaddle()) < paddle->getRectW() / 4.0 * (1 - angleLimitSansPI))
        theta = M_PI_2 - M_PI * (static_cast<double>(pixelOfPaddle() - 1) / paddle->getRectW());
    else{
        if(pixelOfPaddle() > 0)
            theta = M_PI * angleLimitSansPI;
        else
            theta = M_PI - M_PI * angleLimitSansPI;
    }
}


int16_t Ball::pixelOfPaddle(){
    double diff = this->getCenterPointFromLeftEdge() - paddle->getCenterPointFromLeftEdge();
    if(diff < 0)
        diff = floor(diff);
    else if (diff > 0)
        diff = ceil(diff);
    return static_cast<int16_t>(diff);
}

double Ball::getCenterPointFromLeftEdge(){
    return this->getRectX() + static_cast<double>(this->getRectW()) / 2;
}

bool Ball::collidesWithPaddle(){
    if(this->getRectY() + this->getRectH() >= paddle->getRectY() - 1 &&
       this->getRectY() + this->getRectH() <= paddle->getRectY() + paddle->getRectH())
    {
        if(ceil(this->getCenterPointFromLeftEdge()) >= paddle->getRectX() &&
           floor(this->getCenterPointFromLeftEdge()) <= paddle->getRectX() + paddle->getRectW())
            return true;
    }
    return false;
}

void Ball::polarToXY(){
    xSpeed = magnitude * cos(theta);
    ySpeed = -magnitude * sin(theta);
}