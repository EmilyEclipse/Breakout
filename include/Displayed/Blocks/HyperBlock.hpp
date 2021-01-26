#ifndef HYPERBLOCK_HPP
#define HYPERBLOCK_HPP

#include <SDL2/SDL.h>

#include <vector>

#include "Block.hpp"
#include "Rectangle.hpp"
#include "DrawRegistry.hpp"

using std::vector;

class HyperBlock{
public:
    HyperBlock();
    HyperBlock(Uint16 startPosX, Uint16 startPosY, Uint16 *windowWidth,
        DrawRegistry& drawReg);
    
    void handleCollisions(Rectangle *collidingRect);
    void handleRemoveElements();

    Rectangle hyperblockCollider;
    vector<vector<Block>> elements;
    vector<vector<int>> elementsToDelete;
    
    
private:
    DrawRegistry * drawReg;
};

#endif //HYPERBLOCK_HPP