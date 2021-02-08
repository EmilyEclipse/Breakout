#include <SDL2/SDL.h>

#include <gtest/gtest.h>

#include "Rectangle.hpp"
#include "Geometry.hpp"

//RECTANGLE
class RectangleTest : public testing::Test
{
    //Rectangle rectNull(0, 0, 0, 0);
};

TEST_F(RectangleTest, CompletelyOverlapping)
{
    Rectangle rect1(0, 0, 100, 100);
    Rectangle rect2(10, 10, 20, 20);
    EXPECT_TRUE(rect1.collidesRect(rect2));
}

TEST_F(RectangleTest, SameXNoOverlap)
{
    Rectangle rect1(10, 10, 100, 100);
    Rectangle rect2(10, 500, 20, 20);
    EXPECT_FALSE(rect1.collidesRect(rect2));
}

TEST(findSegmentIntersection, Horizontal_1PointIntersection)
{
    Line lin1(Point(0,0), Point(10,0));
    Line lin2(Point(10,0), Point(20, 0));
    Line intersection = Geometry::findSegmentIntersection(lin1, lin2);
    EXPECT_TRUE(intersection.first == intersection.second);
}

TEST(DoSegmentsIntersect, All_Negative_Coordinates)
{
    Line lin1(Point(-2, -1), Point(-2, -3));
    Line lin2(Point(-1, -2), Point(-3, -2));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    Line lin3x(Point(-6, -1), Point(-4, -3));
    Line lin4x(Point(-4, -1), Point(-6, -3));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin3x, lin4x));
    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin4x, lin3x));
}

TEST(DoSegmentsIntersect, All_Positive_Coordinates)
{
    Line lin1(Point(2, 1), Point(2, 3));
    Line lin2(Point(1, 2), Point(3, 2));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));
}

TEST(DoSegmentsIntersect, Positive_Perpendicular_First)
{
    Line lin1(Point(1, 1), Point(1, 3));
    Line lin2(Point(1, 1), Point(3, 1));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin2, lin2);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));
}

TEST(DoSegmentsIntersect, Positive_Perpendicular_Mid)
{
    Line lin1(Point(1, 1), Point(3, 1));
    Line lin2(Point(2, 1), Point(2, 3));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin2, lin1));
}

TEST(DoSegmentsIntersect, Positive_Perpendicular_Mid_Thru)
{
    Line lin1(Point(1, 1), Point(3, 1));
    Line lin2(Point(2, 0), Point(2, 3));

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));

    std::swap(lin2, lin2);

    EXPECT_TRUE(Geometry::doSegmentsIntersect(lin1, lin2));
}

TEST(DoesSegmentIntersectRectangle, Hyper)
{
    Rectangle rect (100, 50, 1720, 245);
    Line segment (Point(960, 540), Point(3224, -1724));

    EXPECT_TRUE(Geometry::doesSegmentIntersectRectangle(segment, rect));
}

TEST(Is_Point_On_Line, Positives_SameFirst)
{
    Line line(Point(1,1), Point(3,3));
    Point p(1,1);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Positives_SameSecond)
{
    Line line(Point(1,1), Point(3,3));
    Point p(3,3);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Positives_PointOnSegment)
{
    Line line(Point(1,1), Point(3,3));
    Point p(2,2);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Positives_PointOffSegment)
{
    Line line(Point(1,1), Point(3,3));
    Point p(4,4);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}




TEST(Is_Point_On_Line, Negatives_SameFirst)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-3,-3);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Negatives_SameSecond)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-1,-1);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Negatives_PointOnSegment)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-2,-2);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Negatives_PointOffSegment)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-5,-5);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
}




TEST(Is_Point_On_Line, Positives_PointOffLine)
{
    Line line(Point(1,1), Point(3,3));
    Point p(5,10);
    ASSERT_FALSE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Negatives_PointOffLine)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-5,-10);
    ASSERT_FALSE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Second_Q)
{
    Line line(Point(-1,1), Point(-3,3));
    Point p(-2,2);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
    p = Point(-10, 2);
    ASSERT_FALSE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Third_Q)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point p(-2,-2);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
    p = Point(-10, -2);
    ASSERT_FALSE(Geometry::isPointOnLine(p, line));
}

TEST(Is_Point_On_Line, Fourth_Q)
{
    Line line(Point(1,-1), Point(3,-3));
    Point p(2,-2);
    ASSERT_TRUE(Geometry::isPointOnLine(p, line));
    p = Point(10, -2);
    ASSERT_FALSE(Geometry::isPointOnLine(p, line));
}



TEST(Is_Point_Right_Of_Line, First_Q)
{
    Line line(Point(1,1), Point(3,3));
    Point right(4, 2);
    Point left(2, 4);
    Point on(2, 2);

    EXPECT_TRUE(Geometry::isPointRightOfLine(right, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(left, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(on, line));
}

TEST(Is_Point_Right_Of_Line, Second_Q)
{
    Line line(Point(-1,1), Point(-3, 3));
    Point right(-2, 3);
    Point left(-3, 2);
    Point on(-2, 2);

    EXPECT_TRUE(Geometry::isPointRightOfLine(right, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(left, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(on, line));
}

TEST(Is_Point_Right_Of_Line, Third_Q)
{
    Line line(Point(-1,-1), Point(-3,-3));
    Point right(-3, -2);
    Point left(-2, -3);
    Point on(-2, -2);

    EXPECT_TRUE(Geometry::isPointRightOfLine(right, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(left, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(on, line));
}

TEST(Is_Point_Right_Of_Line, Fourth_Q)
{
    Line line(Point(1,-1), Point(3,-3));
    Point right(2, -3);
    Point left(3, -2);
    Point on(2, -2);

    EXPECT_TRUE(Geometry::isPointRightOfLine(right, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(left, line));
    EXPECT_FALSE(Geometry::isPointRightOfLine(on, line));
}




TEST(Segment_Crosses_Line, First_Q)
{
    Line lin1(Point(1, 3), Point(3, 1));
    Line lin2(Point(1, 1), Point(3, 3));

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));
}

TEST(Segment_Crosses_Line, Second_Q)
{
    Line lin1(Point(-1, 3), Point(-3, 1));
    Line lin2(Point(-1, 1), Point(-3, 3));

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));
}

TEST(Segment_Crosses_Line, Third_Q)
{
    Line lin1(Point(-1, -3), Point(-3, -1));
    Line lin2(Point(-1, -1), Point(-3, -3));

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));
}

TEST(Segment_Crosses_Line, Fourth_Q)
{
    Line lin1(Point(1, -3), Point(3, -1));
    Line lin2(Point(1, -1), Point(3, -3));

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin1.first, lin1.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));

    std::swap(lin2.first, lin2.second);

    EXPECT_TRUE(Geometry::segmentCrossesLine(lin1, lin2));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);    

    return RUN_ALL_TESTS();
}
