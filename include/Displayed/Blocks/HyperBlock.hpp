#ifndef HYPERBLOCK_HPP
#define HYPERBLOCK_HPP

#include <SDL2/SDL.h>

#include <vector>

#include "Block.hpp"
#include "Rectangle.hpp"
#include "Ball.hpp"

using std::vector;

class HyperBlock{
public:
    HyperBlock(Uint16 startPosX, Uint16 startPosY, Uint16 *windowWidth);
    vector<vector<Block>> elements;

    void handleCollisions(Rectangle *collidingRect);

    Rectangle hyperblockCollider;
private:
    
    vector<vector<int>> elementsToDelete;
    void handleRemoveElements();
};

#endif //HYPERBLOCK_HPP