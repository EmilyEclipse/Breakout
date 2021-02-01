#ifndef HYPERBLOCK_HPP
#define HYPERBLOCK_HPP

#include <SDL2/SDL.h>

#include <list>

#include "Block.hpp"
#include "Rectangle.hpp"
#include "DrawRegistry.hpp"

class HyperBlock{
public:
    HyperBlock();
    HyperBlock(Uint16 startPosX, Uint16 startPosY, Uint16 *windowWidth,
        DrawRegistry& drawReg);
    
    void handleCollisions(Rectangle *collidingRect);
    void handleRemoveElements();

    //using elementsIter = std::list<Block>::iterator;

    Rectangle hyperblockCollider;
    std::list<Block> elements;
    std::list<std::list<Block>::iterator> elementsToDelete;
    
    Uint8 nrOfRows, nrOfCols;
    
private:
    DrawRegistry * drawReg;
};

#endif //HYPERBLOCK_HPP