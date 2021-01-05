#include <SDL2/SDL.h>

#include <gtest/gtest.h>

#include "Rectangle.hpp"

//RECTANGLE
class RectangleTest : testing::Test
{
    Rectangle rect1(0, 0, 0, 0);
};

TEST_F(RectangleTest, CompletelyOverlapping)
{

}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    Rectangle rect1(0, 0, 0, 0);

    

    return RUN_ALL_TESTS();
}
