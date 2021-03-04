#ifndef HYPERBLOCK_HPP
#define HYPERBLOCK_HPP

#include <SDL2/SDL.h>

#include <list>

#include "Block.hpp"
#include "Rectangle.hpp"
#include "DrawRegistry.hpp"
#include "Options.hpp"

class HyperBlock{
public:
    HyperBlock();
    HyperBlock(const Uint16& windowWidth, DrawRegistry& drawReg,
                const Options& options);
    
    void handleCollisions(Rectangle *collidingRect);
    void handleRemoveElements();

    std::list<Block>* getElements();

    void registerForDeletion(std::list<Block>::const_iterator);

    //using elementsIter = std::list<Block>::iterator;

    Rectangle hyperblockCollider;
    
    Uint8 nrOfRows, nrOfCols;
    
private:
    DrawRegistry* drawReg;
    std::list<Block> elements;
    std::list<std::list<Block>::const_iterator> elementsToDelete;
};

#endif //HYPERBLOCK_HPP