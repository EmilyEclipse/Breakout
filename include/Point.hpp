#pragma once

#include <SDL2/SDL.h>

class Point{
public:
    Sint32 x, y;
    Point() : x(0), y(0){}
    Point(Sint32 i_x, Sint32 i_y) : x(i_x), y(i_y) {}

    bool operator == (const Point& rhs){
        return 
            x == rhs.x &&
            y == rhs.y;
    }
};