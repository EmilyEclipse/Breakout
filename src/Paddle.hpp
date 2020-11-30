#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>

#include "Rectangle.hpp"

class Paddle: public Rectangle
{
    using Rectangle::Rectangle; //use the Rectangle class's constructor
public:
    void moveLeft(short amount);
    void moveRight(short amount);
private:
    SDL_Rect rect;
};

#endif //PADDLE_HPP