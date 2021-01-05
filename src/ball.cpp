#include <SDL2/SDL.h>

#include <iterator>

#include "Ball.hpp"
#include "Rectangle.hpp"
#include "Paddle.hpp"


Ball::Ball(Uint16 *i_windowWidth, Uint16 *i_windowHeight, Paddle *i_paddle,
                HyperBlock *i_hyper)
            : Rectangle(*i_windowWidth / 2, *i_windowHeight / 2, 50, 50){
    xSpeed = 7;
    ySpeed = 7;
    magnitude = sqrt(xSpeed * xSpeed + ySpeed * ySpeed);
    windowWidth = i_windowWidth;
    windowHeight = i_windowHeight;
    paddle = i_paddle;
    hyper = i_hyper;
}

void Ball::move(){
    // if(onRightEdge() || onLeftEdge()){
    //     xSpeed *= -1;
    // }
    // if(onTopEdge() || onBottomEdge()){
    //     ySpeed *= -1;
    // }
    handleGenericCollision();
    if(this->collidesWithPaddle())
        handlePaddleCollision();
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


void Ball::handlePaddleCollision(){
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

void Ball::setNecessaryRaysOn(){
    rays[TL].start = this->getTLPoint();
    rays[TR].start = this->getTRPoint();
    rays[BL].start = this->getBLPoint();
    rays[BR].start = this->getBRPoint();

    std::fill(rays.begin(), rays.end(), RayIni());

    if((theta > 0 && theta < M_PI_2) || (theta > M_PI && theta < 3/4 * M_PI)){
        //first or third quadrant
        rays[TL].toggle = true;
        rays[BR].toggle = true;
    } else if ((theta > M_PI_2 && theta < M_PI) ||
                (theta > 3/4 * M_PI && theta < M_2_PI)){
        //second or fourth quadrant
        rays[TR].toggle = true;
        rays[BL].toggle = true;
    } else if (theta == 0 || theta == M_2_PI){
        //points to the right
        rays[TR].toggle = true;
        rays[BR].toggle = true;
    } else if (theta == M_PI_2){
        //points straight up
        rays[TR].toggle = true;
        rays[TL].toggle = true;
    } else if (theta == M_PI){
        //points to the left
        rays[TL].toggle = true;
        rays[BL].toggle = true;
    } else if (theta == 3/4 * M_PI){
        //points straight down
        rays[BR].toggle = true;
        rays[BL].toggle = true;
    }

    collisionRays.clear();

    for(Uint8 i = 0; i < rays.size(); ++i){
        if(rays[i].toggle){
            collisionRays.emplace_back(
                Line(rays[i].start, this->theta, *windowWidth, *windowHeight),
                i
            );
        }
    }
}

bool Ball::tryGetClosestCollidingLineOfRect(Line lin1, Rectangle &i_rect,
        Line &intersectingLine, Line& intersectedLine){
    bool found = false;
    intersectingLine = Line(Point(0,0), Point(0, 10000));
    intersectedLine = Line();

    if(tryIntersection(lin1, i_rect.getTopLine(), intersectingLine)){
        found = true;
        intersectedLine = i_rect.getTopLine();
    }

    if(tryIntersection(lin1, i_rect.getBottomLine(), intersectingLine)){
        found = true;
        intersectedLine = i_rect.getBottomLine();
    }

    if(tryIntersection(lin1, i_rect.getLeftLine(), intersectingLine)){
        found = true;
        intersectedLine = i_rect.getLeftLine();
    }

    if(tryIntersection(lin1, i_rect.getRightLine(), intersectingLine)){
        found = true;
        intersectedLine = i_rect.getRightLine();
    }

    return found;
}

bool Ball::tryIntersection(Line ray, Line rectLine, Line& currentShortest){
    if (Geometry::doSegmentsIntersect(ray, rectLine))
    {
        if(currentShortest.getLength() < Geometry::getRayOriginToLineDistance(ray, rectLine))
        {
            currentShortest = Geometry::getOriginToIntersectionLine(ray, rectLine);
        }
        return true;
    } else {
        return false;
    }
}


void Ball::predictCollisions(){
    Line intersectingLine, intersectedLine;
    Rectangle window(0, 0, *windowWidth, *windowHeight);

    predictions.clear();

    for(auto ray : collisionRays)
    {
        if(Geometry::doesSegmentIntersectRectangle(ray.line,
            hyper->hyperblockCollider))
        {
            //the trajectory intersects the hyperblock,
            //so we'll handle that
            for(auto row : hyper->elements)
                for(auto block : row)
                    if(tryGetClosestCollidingLineOfRect(ray.line, block, intersectingLine,
                        intersectedLine))
                    {
                        predictions.emplace_back(intersectingLine, this, intersectedLine,
                        ray.cornerIndex);
                    }      
        }

        if(Geometry::doSegmentsIntersect(ray.line, window.getTopLine()))
        {
            intersectingLine = Geometry::getOriginToIntersectionLine(
                ray.line, window.getTopLine());
            intersectedLine = window.getTopLine();
            predictions.emplace_back(intersectingLine, this, intersectedLine,
            ray.cornerIndex);
        }
        if(Geometry::doSegmentsIntersect(ray.line, window.getLeftLine()))
        {
            intersectingLine = Geometry::getOriginToIntersectionLine(
                ray.line, window.getLeftLine());
            intersectedLine = window.getLeftLine();
            predictions.emplace_back(intersectingLine, this, intersectedLine,
            ray.cornerIndex);
        }
        if(Geometry::doSegmentsIntersect(ray.line, window.getRightLine()))
        {
            intersectingLine = Geometry::getOriginToIntersectionLine(
                ray.line, window.getRightLine());
            intersectedLine = window.getRightLine();
            predictions.emplace_back(intersectingLine, this, intersectedLine,
            ray.cornerIndex);
        }
    }
}

void Ball::letOnlyClosestCollision()
{
    if(!predictions.empty())
    {
        auto minCollision = std::min_element(predictions.begin(), predictions.end(),
                                [](const GenericCollision a, const GenericCollision b)
                                {
                                    return a.originalDistance < b.originalDistance;
                                } );
        
        predictions[0] = *minCollision;
        predictions.resize(1);
    }
}

void Ball::handleGenericCollision(){
    //\/ should only be done when the previous prediction expires
    if(predictions.empty())
    {
        predictCollisions();
        letOnlyClosestCollision();
    } else {
        //a collision prediction exists
        GenericCollision& prediction = predictions[0];
        if(prediction.framesAhead >= 1)
        {
            --prediction.framesAhead;
        } else {
            //doing the actual collision
            polarToXY();
            if(prediction.intersectedLine.isVertical()) {
                xSpeed *= -1;
            } else if(prediction.intersectedLine.isHorizontal()) {
                ySpeed *= -1;
            }

            //teleport the ball in the appropriate spot
            teleportBallByCorner(prediction.cornerIndex, prediction.x, prediction.y);
            predictions.clear();
        }
    }
}

void Ball::teleportBallByCorner(Uint8 cornerIndex, Uint16 x, Uint16 y)
{
    switch(cornerIndex){
    case TL:
        this->setRectX(x);
        this->setRectY(y);
        break;
    case TR:
        this->setRectX(x - this->getRectW());
        this->setRectY(y);
    case BL:
        this->setRectX(x);
        this->setRectY(y - this->getRectH());
    case BR:
        this->setRectX(x - this->getRectW());
        this->setRectY(y - this->getRectH());
    }
}