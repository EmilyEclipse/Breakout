#include <SDL2/SDL.h>

#include <iterator>

#include "Ball.hpp"
#include "Rectangle.hpp"
#include "Paddle.hpp"
#include "ScoreKeeper.hpp"
#include "Options.hpp"
#include "Util.hpp"

#include "Draw.hpp"


Ball::Ball(Options& options, Paddle& i_paddle, HyperBlock& i_hyper,
    ScoreKeeper& i_SK, AudioManager& i_AM)
    :   Rectangle(options.windowWidth / 2, options.windowHeight / 2,
                  50 * options.xScale, 50 * options.yScale,
                  0, 0xFF, 0xF4, 0x4F),
        windowWidth(&options.windowWidth), windowHeight(&options.windowHeight),
        paddle(&i_paddle), hyper(&i_hyper),
        scoreKeeper(&i_SK), audioManager(&i_AM)
{
    xSpeed = 7 * options.xScale;
    ySpeed = -7 * options.yScale;
    magnitude = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
}

void Ball::move(){
    // if(onRightEdge() || onLeftEdge()){
    //     xSpeed *= -1;
    // }
    // if(onTopEdge() || onBottomEdge()){
    //     ySpeed *= -1;
    // }
    handleScreenCollison();
    handleBlockCollision();
    if(this->collidesWithPaddle())
        handlePaddleCollision();
    moveX();
    moveY();
}

void Ball::moveX(){
    setRectX(getRectX() + xSpeed * speedFactor);
}

void Ball::moveY(){
    setRectY(getRectY() + ySpeed * speedFactor);
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


void Ball::handlePaddleCollision(){
    //Number of exit angles is 'paddle_width', plus another one for the paddle's center pixel
    //if the position of that pixel is an integer (otherwise it's just imaginary)
    calculateThetaForCollision();
    polarToXY();
    audioManager->playSample(audioManager->BLEEP);
}

void Ball::calculateThetaForCollision(){

    if(pixelOfPaddle() == 0){
        theta = M_PI_2;
    } else if(abs(pixelOfPaddle()) < paddle->getRectW() / 4.0 * (1 - angleLimitSansPI))
        theta = M_PI_2 - M_PI * (static_cast<double>(pixelOfPaddle() - 1) / paddle->getRectW());
    else {
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



// void Ball::teleportBallByCorner(Uint8 cornerIndex, Uint16 x, Uint16 y)
// {
//     switch(cornerIndex){
//     case TL:
//         this->setRectX(x);
//         this->setRectY(y);
//         break;
//     case TR:
//         this->setRectX(x - this->getRectW());
//         this->setRectY(y);
//     case BL:
//         this->setRectX(x);
//         this->setRectY(y - this->getRectH());
//     case BR:
//         this->setRectX(x - this->getRectW());
//         this->setRectY(y - this->getRectH());
//     }
// }

void Ball::thetaFromXY()
{
    this->theta = atan2(-ySpeed, xSpeed);
}

void Ball::handleScreenCollison()
{
    bool collided = false;
    if(this->onLeftEdge())
    {
        collided = true;
        if(xSpeed < 0)
            xSpeed *= -1;
    }
    
    if(this->onRightEdge())
    {
        collided = true;
        if(xSpeed > 0)
            xSpeed *= -1;
    }
    
    if(this->onTopEdge())
    {
        collided = true;
        if(ySpeed < 0)
            ySpeed *= -1;
    }

    if(this->onBottomEdge())
    {
        collided = true;
        if(ySpeed > 0)
            ySpeed *= -1;
    }

    if(collided)
        audioManager->playSample(audioManager->sfx::BLOOP);
}

void Ball::handleBlockCollision()
{
    bool collidedBlock = false;

    if(this->collidesRect(hyper->hyperblockCollider))
        for(auto block_iter = hyper->getElements()->begin(); block_iter != hyper->getElements()->end(); ++block_iter)
        {
            if(this->collidesRect(*block_iter))
            {
                if(block_iter->containsPoint(getTLPoint()) ||
                    block_iter->containsPoint(getTRPoint()))
                {   //top of ball collision
                    if(ySpeed < 0)
                        ySpeed *= -1;
                } else if (block_iter->containsPoint(getBLPoint()) ||
                    block_iter->containsPoint(getBRPoint()))
                {   //bottom of ball collision
                    if(ySpeed > 0)
                        ySpeed *= -1;
                } else if(block_iter->containsPoint(getTLPoint()) ||
                    block_iter->containsPoint(getBLPoint()))
                {   //left side of ball collision
                    if(xSpeed < 0)
                        xSpeed *= -1;
                } else if(block_iter->containsPoint(getTLPoint()) ||
                    block_iter->containsPoint(getBLPoint()))
                {   //right side of ball collision
                    if(xSpeed > 0)
                        xSpeed *= -1;
                }

                audioManager->playSample(audioManager->sfx::BLEEP);

                Uint8 blockRow = 1 + hyper->nrOfCols - 
                        floor((block_iter->getID() + 1) / hyper->nrOfCols);
                Uint16 blockValue = blockRow * 150;

                if(blockRow > hyper->getHighestCollidedRow())
                {
                    hyper->setHighestCollidedRow(blockRow);
                    this->setSpeedFactor(1 + 0.2 * blockRow);
                }
                    

                scoreKeeper->incrementScore(blockValue);

                hyper->registerForDeletion(block_iter);
                collidedBlock = true;
                break;
            }
        }

    if(collidedBlock)
    {
        hyper->handleRemoveElements();
        collidedBlock = false;
    }
}

void Ball::setSpeedFactor(double i_speedFactor)
{
    this->speedFactor = i_speedFactor;
}