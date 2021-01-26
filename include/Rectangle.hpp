#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

#include "Drawable.hpp"
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

    bool collidesRect( Rectangle& inputRectangle);
    bool collidesUpDown( Rectangle& inputRectangle);
    bool collidesLeftRight( Rectangle& inputRectangle);
    bool containsPoint(const Point& inputPoint);

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

    Uint8 getRed() const;
    Uint8 getGreen() const;
    Uint8 getBlue() const;

    Rectangle* getRectangle();
    
    Sint32 getLayer() const;
    Uint32 getID() const;
    void setID(Uint32 input);

private:
    SDL_Rect rect;
    Sint32 layer;
    Uint8 red, green, blue;
    Uint32 id;
};

#endif //RECTANGLE_HPP