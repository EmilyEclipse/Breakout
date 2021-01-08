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

    bool collidesRect( Rectangle& inputRectangle);
    bool collidesUpDown( Rectangle& inputRectangle);
    bool collidesLeftRight( Rectangle& inputRectangle);

    Sint32 getTopEdge() ;
    Sint32 getBottomEdge() ;
    Sint32 getLeftEdge() ;
    Sint32 getRightEdge() ;

    Line getTopLine() ;
    Line getBottomLine() ;
    Line getLeftLine() ;
    Line getRightLine() ;

    Point getTLPoint() ;
    Point getTRPoint() ;
    Point getBLPoint() ;
    Point getBRPoint() ;

    void setRectX(Sint32 value);
    void setRectY(Sint32 value);
    void setRectW(Sint32 value);
    void setRectH(Sint32 value);

    Sint32 getRectX() ;
    Sint32 getRectY() ;
    Sint32 getRectW() ;
    Sint32 getRectH() ;

private:
    SDL_Rect rect;
};

#endif //RECTANGLE_HPP