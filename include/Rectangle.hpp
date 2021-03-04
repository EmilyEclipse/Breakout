#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

#include "Point.hpp"
#include "Line.hpp"

class Rectangle{
public:
    Rectangle();
    Rectangle(short x, short y, short w, short h);
    Rectangle(short x, short y, short w, short h, Sint16 layer,
                Uint8 red, Uint8 green, Uint8 blue);
    Rectangle(Point first, Point second);

    const SDL_Rect* getRect() const;

    bool collidesRect(const Rectangle& inputRectangle) const;
    bool collidesUpDown(const Rectangle& inputRectangle)const;
    bool collidesLeftRight(const Rectangle& inputRectangle) const;
    bool containsPoint(const Point& inputPoint) const;

    Sint32 getTopEdge() const;
    Sint32 getBottomEdge() const;
    Sint32 getLeftEdge() const;
    Sint32 getRightEdge() const;

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

    Sint32 getRectX() const;
    Sint32 getRectY() const;
    Sint32 getRectW() const;
    Sint32 getRectH() const;

    Uint8 getRed() const;
    Uint8 getGreen() const;
    Uint8 getBlue() const;

    const Rectangle* getRectangle() const;
    
    Sint32 getLayer() const;

private:
    SDL_Rect rect;
    Sint32 layer;
    Uint8 red, green, blue;
};

#endif //RECTANGLE_HPP