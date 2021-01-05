#pragma once

#include <SDL2/SDL.h>

class Point{
public:
    Uint16 x, y;
    Point(){
        this->x = 0;
        this->y = 0;
    }
    Point(Uint16 i_x, Uint16 i_y){
        this->x = i_x;
        this->y = i_y;
    }

    bool operator == (const Point& rhs){
        return 
            x == rhs.x &&
            y == rhs.y;
    }
};