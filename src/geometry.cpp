#include <algorithm>
#include <utility>

#include "Rectangle.hpp"
#include "Geometry.hpp"

double Geometry::crossProduct(Point a, Point b){
    return (a.x * b.y - a.y * b.x);
}

bool Geometry::isPointRightOfLine(Point input_point, Line line){
    line.orderPointsByX();

    //Moving reference frame so that one point of the `line` is at the origin.
    //Variables with "originated" in their name have had this transformation done
    //to them.

    Line originatedLine;
    Point crossPoint; //Point of originatedLine that's not the origin;
    if (line.first.x < 0 && line.second.x > 0)
    {   //across
        if(line.first.y < 0 && line.second.y < 0)
        {   //both below
            rotate90DegCCW(line);
            rotate90DegCCW(input_point);
        } else if(line.first.y >= 0 && line.second.y >= 0)
        {
            //both above
            rotate270DegCCW(line);
            rotate270DegCCW(input_point);
        }
        
    }

    if(line.first.x >= 0 && line.second.x >= 0)
    {
        //Use rule 1#
        originatedLine = Line (   
        Point(0,0),
        Point(
            line.second.x - line.first.x,
            line.second.y - line.first.y
            )
        );
        crossPoint = originatedLine.second;
    } else if(line.first.x < 0 && line.second.x < 0)
    {
        //Use rule 2#
        originatedLine = Line (   
        Point(
            line.first.x - line.second.x,
            line.first.y - line.second.y
            ),
        Point(0,0)
        );
        crossPoint = originatedLine.first;
    } else if(line.first.x < 0 && line.second.x > 0)
    {
        Line XAxis(Point(0,0), Point(INT32_MAX, 0));
        Line YAxis(Point(0,0), Point(0, INT32_MAX));
        //if((line.first.y < 0 && line.second.y > 0))
        if(Geometry::findSegmentIntersection(line, XAxis).first.x > 0)
        {
            //Use rule 1#
            originatedLine = Line (   
            Point(0,0),
            Point(
                line.second.x - line.first.x,
                line.second.y - line.first.y
                )
            );
            crossPoint = originatedLine.second;
        } else {
            //Use rule 2#
            originatedLine = Line (   
            Point(
                line.first.x - line.second.x,
                line.first.y - line.second.y
                ),
            Point(0,0)
            );
            crossPoint = originatedLine.first;
        }
    }

    // if(input_point.x < 0)
    // {
    //     if(input_point.y >= 0)
    //     {
    //         //Second Quadrant
    //         Geometry::rotate180Deg(input_point);
    //         Geometry::rotate180Deg(line);
    //     } else  {
    //         //Third Quadrant
    //         Geometry::rotate90DegCCW(input_point);
    //         Geometry::rotate90DegCCW(line);
    //     }
    // }

    
    
    
    Point originatedInputPoint(input_point.x - line.first.x, input_point.y - line.first.y);

    // if(originatedLine.second.y < 0){
    //     rotate90DegCCW(originatedLine);
    //     rotate90DegCCW(originatedInputPoint);
    // }

    double result = crossProduct(crossPoint, originatedInputPoint);
    return result < 0;
}

bool Geometry::segmentCrossesLine(Line lin1, Line lin2){
    bool isFirstRight = isPointRightOfLine(lin1.first, lin2);
    bool isSecondRight = isPointRightOfLine(lin1.second, lin2);
    if(isFirstRight && isSecondRight)
        return false;
    else if(isFirstRight || isSecondRight)
        return true;
    else
        return false;   
}


bool Geometry::segmentTouchesOrCrossesLine(Line lin1, Line lin2){
    return  isPointOnLine(lin1.first, lin2) ||
            isPointOnLine(lin1.second, lin2) ||
            segmentCrossesLine(lin1, lin2);
}

bool Geometry::isPointOnLine(Point input_point, Line line){
     const double acceptable_error = 10e-5;

    line.orderPointsByX();

    //Moving reference frame so that the first point of the line is at the origin.
    //Variables with "originated" in their name have had this transformation done
    //to them.
    //Point origin(0,0);
    //Point originatedLineFirst(0,0);
    Line originatedLine(
        Point(0,0),
        Point(
            line.second.x - line.first.x,
            line.second.y - line.first.y)
        );
    
    Point originatedInputPoint( input_point.x - line.first.x,
                                input_point.y - line.first.y);

    // if(originatedLine.second.y < 0){
    //     rotate90DegCCW(originatedLine);
    //     rotate90DegCCW(originatedInputPoint);
    // }

    double result = crossProduct(originatedLine.second, originatedInputPoint);
    if(abs(result) < acceptable_error)
        return true;
    else
        return false;
}

bool Geometry::doSegmentsIntersect(Line lin1, Line lin2){
    Rectangle lin1Coll(lin1.first, lin1.second);
    Rectangle lin2Coll(lin2.first, lin2.second);

    return  lin1Coll.collidesRect(lin2Coll) &&
            segmentTouchesOrCrossesLine(lin1, lin2) &&
            segmentTouchesOrCrossesLine(lin2, lin1);
}

//Finds the intersection of two segments when it is known that one exists
Line Geometry::findSegmentIntersection(Line lin1, Line lin2){
    /*  The intersection is a line with the points "first" and "second"
        at it's ends. If the intersection is a point, first will have the same
        coordinates as second
    */

   Point interFirst, interSecond;

   if(lin1.first.x == lin1.second.x){
        //Case (A)
        //first line is vertical =>
        interFirst.x = lin1.first.x;
        interSecond.x = interFirst.x;

        if(lin2.first.x == lin2.second.x){
            //Case (AA)
            //vertical intersection
            
            normalizeLinesByY(lin1, lin2);
            
            // Now we know that the y-value of a["first"] is the
            // lowest of all 4 y values
            // this means, we are either in case (AAA):
            //   lin1: x--------------x
            //   lin2:    x---------------x
            // or in case (AAB)
            //   lin1: x--------------x
            //   lin2:    x-------x
            // in both cases:
            // get the relavant y intervall

            interFirst.y = lin2.first.y;
            interSecond.y = std::min(lin1.second.y, lin2.second.y);
        } else {
            // Case (AB)
            
            handleSlopedLine(lin2, interFirst, interSecond);
        }
    } else if(lin2.first.x == lin2.second.x){
        // Case (B)
        // essentially the same as Case (AB), but with
        // lin1 and lin2 switched
        std::swap(lin1, lin2);

        interFirst.x = lin1.first.x;
        interSecond.x = interFirst.x;

        handleSlopedLine(lin2, interFirst, interSecond);
    } else {
        // Case (C)
        // Both lines can be represented mathematically

        double slope1, slope2, t1, t2;
        slope1 = calculateSlope(lin1);
        slope2 = calculateSlope(lin2);
        t1 = calculateOffset(lin1, slope1);
        t2 = calculateOffset(lin2, slope2);

        if(slope1 == slope2){
            // Case (CA)
            // both lines are in parallel. As we know that they
            // intersect, the intersection could be a line
            // when we rotated this, it would be the same situation
            // as in case (AA)
            normalizeLinesByX(lin1, lin2);

            // get the relavant x interval
            interFirst.x = lin2.first.x;
            interSecond.x = std::min(lin1.second.x, lin2.second.x);

            interFirst.y = slope1 * interFirst.x + t1;
            interSecond.y = slope2 * interSecond.x + t2;
        } else {
            // Case (CB): only a point as intersection:
            // y = ma*x+ta
            // y = mb*x+tb
            // ma*x + ta = mb*x + tb
            // (ma-mb)*x = tb - ta
            // x = (tb - ta)/(ma-mb)

            interFirst.x = (t2 - t1) / (slope1 - slope2);
            interFirst.y = slope1 * interFirst.x + t1;
            interSecond = interFirst;
        }
    }

    return Line(interFirst, interSecond);
}



void Geometry::normalizeLinesByX(Line &lin1, Line &lin2){
    // Let's normalize the points,
    // so that lin1.first.x < lin1.second.x
    // and lin2.first.x < lin2.second.x
    // and lin1.first.x < lin2.first.x

    if(lin1.first.x > lin1.second.x)
        std::swap(lin1.first, lin1.second);
    if(lin2.first.x > lin2.second.x)
        std::swap(lin2.first, lin2.second);
    if(lin1.first.x > lin2.first.x)
        std::swap(lin1, lin2);
}

void Geometry::normalizeLinesByY(Line &lin1, Line &lin2){
    // Let's normalize the points,
    // so that lin1.first.y < lin1.second.y
    // and lin2.first.y < lin2.second.y
    // and lin1.first.y < lin2.first.y

    if(lin1.first.y > lin1.second.y)
        std::swap(lin1.first, lin1.second);
    if(lin2.first.y > lin2.second.y)
        std::swap(lin2.first, lin2.second);
    if(lin1.first.y > lin2.first.y)
        std::swap(lin1, lin2);
}

void Geometry::handleSlopedLine(Line slopedLine, Point &interFirst, Point &interSecond){
    // we can mathematically represent line lin2 as
    //     y = m*x + t <=> t = y - m*x
    // m = (y1-y2)/(x1-x2)
    double slope, t;

    slope = calculateSlope(slopedLine);

    t = calculateOffset(slopedLine, slope);

    interFirst.y = slope * interFirst.x + t;
    interSecond.y = interFirst.y;
}

double Geometry::calculateSlope(Line i_line){
    return  (i_line.second.y - i_line.first.y) /
            (i_line.second.x - i_line.first.x);
}

double Geometry::calculateOffset(Line i_line, double slope){
    return i_line.first.y - slope * i_line.first.x;
}

bool Geometry::doesSegmentIntersectRectangle(Line lin1, Rectangle i_rect){
    return doSegmentsIntersect(lin1, i_rect.getTopLine()) ||
        doSegmentsIntersect(lin1, i_rect.getBottomLine()) ||
        doSegmentsIntersect(lin1, i_rect.getLeftLine()) ||
        doSegmentsIntersect(lin1, i_rect.getRightLine());
}

double Geometry::getRayOriginToLineDistance(Line ray, Line lin){
    Line intersection = findSegmentIntersection(ray, lin);

    if(intersection.first == intersection.second){
        Line interLine(ray.first, intersection.first);
        return interLine.getLength();
    } else {
        Line interLine1(ray.first, intersection.first);
        Line interLine2(ray.first, intersection.second);

        return std::min(interLine1.getLength(), interLine2.getLength());
    }
}

Line Geometry::getOriginToIntersectionLine(Line ray, Line lin){
    Line intersection = findSegmentIntersection(ray, lin);

    if(intersection.first == intersection.second){
        Line interLine(ray.first, intersection.first);
        return interLine;
    } else {
        Line interLine1(ray.first, intersection.first);
        Line interLine2(ray.first, intersection.second);

        if(interLine1.getLength() < interLine2.getLength())
            return interLine1;
        else
            return interLine2;
    }
}

void Geometry::rotate90DegCCW(Point& input)
{
    std::swap(input.x, input.y);
    input.x *= -1;
}

void Geometry::rotate180Deg(Point& input)
{
    input.x *= -1;
    input.y *= -1;
}

void Geometry::rotate270DegCCW(Point& input)
{
    std::swap(input.x, input.y);
    input.x *= -1;
    input.y *= -1;
}

void Geometry::rotate90DegCCW(Line& input)
{
    rotate90DegCCW(input.first);
    rotate90DegCCW(input.second);
}

void Geometry::rotate180Deg(Line& input)
{
    rotate180Deg(input.first);
    rotate180Deg(input.second);
}

void Geometry::rotate270DegCCW(Line& input)
{
    rotate270DegCCW(input.first);
    rotate270DegCCW(input.second);
}

void Geometry::normalizeAngleRad(double& theta)
{
    const double Math2PI = 2 * M_PI;
    theta = fmod(theta, Math2PI); //makes theta be in interval (-2pi, 2pi)
    if(theta < 0)
    {
        theta = 2 * M_PI + theta;
    }
}