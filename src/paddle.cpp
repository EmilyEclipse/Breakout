#include <SDL2/SDL.h>

#include "Paddle.hpp"


void Paddle::moveLeft(short amount){
    setRectX(getRect()->x - amount);
}

void Paddle::moveRight(short amount){
    setRectX(getRect()->x + amount);
}