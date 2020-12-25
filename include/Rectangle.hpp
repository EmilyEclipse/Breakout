#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

class Rectangle
{
public:
    Rectangle();
    Rectangle(short x, short y, short w, short h);

    SDL_Rect* getRect();

    bool collidesRect(Rectangle *inputRect);
    bool collidesUpDown(Rectangle *inputRectangle);
    bool collidesLeftRight(Rectangle *inputRectangle);

    Uint16 getTopEdge();
    Uint16 getBottomEdge();
    Uint16 getLeftEdge();
    Uint16 getRightEdge();

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