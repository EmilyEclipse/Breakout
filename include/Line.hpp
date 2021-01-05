#pragma once

#include <algorithm>

#include "Point.hpp"

class Line{
public:
    Point first, second;

    Line(){
        first = Point();
        second = Point();
    }

    Line(Point i_a, Point i_b){
        this->first = i_a;
        this->second = i_b;
    }

    Line(Point start, double heading, double magnitude){
        Uint16 offX = magnitude * cos(heading);
        Uint16 offY = -magnitude * sin(heading);

        Point finish(start.x + offX, start.y + offY);
        Line(start, finish);
    }

    Line(Point start, double heading, Uint16 windowWidth, Uint16 windowHeight){
        Uint16 maxLength = sqrt(windowWidth * windowWidth +
                                windowHeight * windowHeight) + 10;

        Line(start, heading, maxLength);
    }

    bool isVertical(){
        return first.x == second.x;
    }

    bool isHorizontal(){
        return first.y == second.y;
    }

    double getLength(){
        if(first == second)
            return 0;
        else if(first.x == second.x){
            //vertical line
            return abs(first.y - second.y);
        } else if(first.y == second.y){
            //horizontal line
            return abs(first.y - second.y);
        } else {
            //oblique => Pythagoras'
            Uint16 absDiffX = abs(first.x - second.x);
            Uint16 absDiffY = abs(first.y - second.y);

            return sqrt(absDiffX * absDiffX + absDiffY * absDiffY);
        }
    }
};