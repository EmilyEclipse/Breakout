#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

class Rectangle
{
public:
    Rectangle(short x, short y, short w, short h);

    SDL_Rect* getRect();
    void setRectX(short value);
    void setRectY(short value);
    // void moveX(short moveX);
    // void moveY(short moveY);
private:
    SDL_Rect rect;
};

#endif //RECTANGLE_HPP