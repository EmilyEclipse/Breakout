#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

#include "Point.hpp"
#include "Line.hpp"

class Rectangle
{
public:
    Rectangle();
    Rectangle(short x, short y, short w, short h);
    Rectangle(Point first, Point second);

    SDL_Rect* getRect();

    bool collidesRect(Rectangle *inputRect);
    bool collidesUpDown(Rectangle *inputRectangle);
    bool collidesLeftRight(Rectangle *inputRectangle);

    Uint16 getTopEdge();
    Uint16 getBottomEdge();
    Uint16 getLeftEdge();
    Uint16 getRightEdge();

    Line getTopLine();
    Line getBottomLine();
    Line getLeftLine();
    Line getRightLine();

    Point getTLPoint();
    Point getTRPoint();
    Point getBLPoint();
    Point getBRPoint();

    void setRectX(short value);
    void setRectY(short value);
    void setRectW(short value);
    void setRectH(short value);

    short getRectX();
    short getRectY();
    short getRectW();
    short getRectH();
private:

    SDL_Rect rect;
};

#endif //RECTANGLE_HPP