#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"
#include "HyperBlock.hpp"
#include "Geometry.hpp"
#include "Paddle.hpp"

class Ball: public Rectangle{
public:
    Ball(Uint16 *i_windowWidth, Uint16 *i_windowHeight, Paddle *i_paddle,
            HyperBlock *i_hyper);
    void move();

private:
    struct RayIni{
        Point start;
        bool toggle;

        RayIni(){
            start = Point();
            toggle = false;
        }
    };

    vector<RayIni> rayInis;
    enum raysEnum{TL = 0, TR, BL, BR};

    //object for collisions with walls, the ceiling, or the blocks
    struct GenericCollision{
        Uint16 x, y;
        double framesAhead;
        double originalDistance;
        Line intersectedLine;
        Uint8 cornerIndex;

        GenericCollision(){
            x = 0;
            y = 0;
            framesAhead = 0;
            originalDistance = 0;
        }

        //Takes a ray line with it's origin on a corner of the ball
        //and it's other point on one pixel of a block or wall
        GenericCollision(Line intersectingLine, Ball* ball, Line i_intersectedLine,
        Uint8 corner){
            x = intersectingLine.second.x;
            y = intersectingLine.second.y;
            originalDistance = intersectingLine.getLength();
            framesAhead = calculateFramesTo(ball);
            intersectedLine = i_intersectedLine;
            cornerIndex = corner;
        }


        double calculateFramesTo(Ball* ball){
            return this->originalDistance / ball->magnitude;
        }

        //void calculateNext(Uint16 *windowWidth, HyperBlock *hyper);
    };

    struct Ray {
        Line line;
        Uint8 cornerIndex;

        Ray(Line line, Uint8 cornerIndex){
            this->line = line;
            this->cornerIndex = cornerIndex;
        }
    };

    vector<GenericCollision> predictions;

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

    void setNecessaryRaysOn();
    void predictCollisions();
    bool tryGetClosestCollidingLineOfRect(Line lin, Rectangle &rect, Line &closestColl, 
                                            Line& intersectedLine);
    bool tryIntersection(Line ray, Line rectLine, Line& currentShortest);
    void letOnlyClosestCollision();
    void handleGenericCollision();
    
    void teleportBallByCorner(Uint8 cornerIndex, Uint16 x, Uint16 y);
    void thetaFromXY();

    std::vector<Ray> collisionRays;

    double xSpeed;
    double ySpeed;
    const double angleLimitSansPI = static_cast<double>(1) / 3;
    double magnitude;
    double theta;
    Uint16 *windowWidth, *windowHeight;
    Paddle *paddle;
    HyperBlock *hyper;
};

#endif //BALL_HPP