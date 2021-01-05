#pragma once

#include <SDL2/SDL.h>

#include "Point.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"

class Geometry{
public:
    static bool isPointOnLine(Point a, Line line);
    static bool isPointRightOfLine(Point a, Line line);
    static bool segmentTouchesOrCrossesLine(Line lin1, Line lin2);
    static bool segmentCrossesLine(Line lin1, Line lin2);
    static double crossProduct(Point a, Point b);

    static bool doSegmentsIntersect(Line lin1, Line lin2);
    static bool doesSegmentIntersectRectangle(Line lin1, Rectangle i_rect);

    static Line findSegmentIntersection(Line lin1, Line lin2);
    static double getRayOriginToLineDistance(Line ray, Line lin);

    static Line getOriginToIntersectionLine(Line ray, Line lin);

    static void normalizeLinesByX(Line &lin1, Line &lin2);
    static void normalizeLinesByY(Line &lin1, Line &lin2);

private:
    static void handleSlopedLine(Line slopedLine, Point &interFirst, Point &interSecond);

    static double calculateSlope(Line i_line);
    static double calculateOffset(Line i_line, double slope);
};