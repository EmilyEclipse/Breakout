#include <SDL2/SDL.h>

#include "Block.hpp"
#include "Row.hpp"
#include "HyperBlock.hpp"

Block::Block(Uint16 x, Uint16 y, Uint16 w, Uint16 h, uint8_t red, uint8_t green,
        uint8_t blue)
        : Rectangle(x, y, w, h)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Row::Row(Uint8 numberOfBlocks, Uint16 startPosX, Uint16 startPosY, Uint16 blockH,
         Uint8 blockSpacingX, Uint16 *windowWidth,
         Uint8 red, Uint8 green, Uint8 blue)
{
    Uint8 blockW = calculateBlockWidth(*windowWidth, numberOfBlocks, startPosX, blockSpacingX);

    //add blocks to row
    for(int i = 0; i < numberOfBlocks; ++i){
        Uint16 blockX = startPosX + i * (blockW + blockSpacingX);
        Block block(blockX, startPosY, blockW, blockH, red, green, blue);
        elements.push_back(block);
    }

    //create rect surrounding the row for use in collisions
    Uint16 rowWidth = (blockW + blockSpacingX) * numberOfBlocks - blockSpacingX;
    Uint16 rowHeight = blockH;
    Rectangle container(startPosX, startPosY, rowWidth, rowHeight);
    this->rowCollider = container;
}

Uint8 Row::calculateBlockWidth(
    Uint16 windowWidth, Uint8 numberOfBlocks, Uint16 startPosX, Uint8 blockSpacingX){
    return (windowWidth - 2 * startPosX) / numberOfBlocks - blockSpacingX;
}

HyperBlock::HyperBlock(Uint16 startPosX, Uint16 startPosY, Uint16 *windowWidth)
{
    Uint16 blockH = 20;
    Uint8 blockSpacingX = 10;
    Uint8 blockSpacingY = 10;
    Uint8 blocksPerRow = 5;
    

    //add rows to HyperBlock
    Row red     (blocksPerRow, 50, 50, blockH, blockSpacingX, windowWidth, 0xFF, 0x24, 0x00);
    Row orange  (blocksPerRow, 50, 60, blockH, blockSpacingX, windowWidth, 0xFF, 0x9F, 0x00);
    Row green   (blocksPerRow, 50, 70, blockH, blockSpacingX, windowWidth, 0x4C, 0xBB, 0x17);
    Row blue    (blocksPerRow, 50, 80, blockH, blockSpacingX, windowWidth, 0x00, 0x73, 0xCF);

    this->elements.push_back(red.elements);
    this->elements.push_back(orange.elements);
    this->elements.push_back(green.elements);
    this->elements.push_back(blue.elements);

    //make HyperBlock colliding box
    Uint8 nrOfColumns = this->elements.size();

    Uint16 rowWidth = *windowWidth - 2 * startPosX;
    Uint16 rowHeight = (blockH + blockSpacingY) * nrOfColumns - blockSpacingY;
    Rectangle collidingBox(startPosX, startPosY, rowWidth, rowHeight);
    hyperblockCollider = collidingBox;

    
}