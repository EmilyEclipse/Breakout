#include <SDL2/SDL.h>

#include <algorithm>
#include <list>
#include <vector>
#include <tuple>
#include <utility>

#include "Displayed/Blocks/Block.hpp"
#include "Displayed/Blocks/Row.hpp"
#include "Displayed/Blocks/HyperBlock.hpp"
#include "DrawRegistry.hpp"
#include "Options.hpp"

Uint16 Block::ID_Counter = 0;

Block::Block(Uint16 x, Uint16 y, Uint16 w, Uint16 h,
    Uint8 red, Uint8 green, Uint8 blue)
    :   Rectangle(x, y, w, h, 20, red, green, blue),
        ID(Block::ID_Counter++)
{}

void Block::initID()
{
    Block::ID_Counter = 0;
}

const Uint16 Block::getID() const
{
    return this->ID;
}

Row::Row(Uint8 numberOfBlocks, Uint16 startPosX, Uint16 startPosY, Uint16 blockH,
         Uint8 blockSpacingX, const Uint16& windowWidth,
         Uint8 red, Uint8 green, Uint8 blue)
{
    Uint16 blockW = calculateBlockWidth(windowWidth, numberOfBlocks, startPosX, blockSpacingX);

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

Uint16 Row::calculateBlockWidth(
    Uint16 windowWidth, Uint8 numberOfBlocks, Uint16 startPosX, Uint8 blockSpacingX){
    return (windowWidth - 2 * startPosX) / numberOfBlocks - blockSpacingX;
}

HyperBlock::HyperBlock(){}

HyperBlock::HyperBlock(DrawRegistry& i_drawReg,
    const Options& options)
    : drawReg(&i_drawReg)
{
    const double& xScale = options.xScale;
    const double& yScale = options.yScale;
    const Uint16 windowWidth = options.windowWidth;
    Uint16 startPosX = 100 * xScale;
    Uint16 startPosY = 150 * yScale;
    Uint16 blockH = 50 * yScale;
    Uint16 blockSpacingX = 15 * xScale;
    Uint16 blockSpacingY = 15 * yScale;
    Uint16 blocksPerRow = 5;

    Block::initID();
    

    //add rows to HyperBlock
    std::vector<std::tuple<Uint8, Uint8, Uint8>> rowColors = 
        {
            {0xFF, 0x24, 0x00}, //red
            {0xFF, 0x9F, 0x00}, //orange
            {0x4C, 0xBB, 0x17}, //green
            {0x00, 0x73, 0xCF}  //blue
        };

    for(Uint8 i = 0; i < rowColors.size(); ++i)
    {
        Uint16 rowStartPosY = startPosY + i * (blockH + blockSpacingY);
        Row currentRow (
                blocksPerRow, startPosX, rowStartPosY, blockH, blockSpacingX,
                windowWidth, std::get<0>(rowColors[i]), std::get<1>(rowColors[i]),
                std::get<2>(rowColors[i]));
        this->elements.splice(this->elements.end(), currentRow.elements);
    }

    //make HyperBlock colliding box
    nrOfRows = rowColors.size();
    nrOfCols = blocksPerRow;

    Uint16 rowWidth = windowWidth - 2 * startPosX;
    Uint16 colliderHeight = (blockH + blockSpacingY) * nrOfRows - blockSpacingY;
    Rectangle collidingBox(startPosX, startPosY, rowWidth, colliderHeight);
    hyperblockCollider = collidingBox;
}

void HyperBlock::handleRemoveElements()
{
    for(auto delete_el_iter = elementsToDelete.begin(); delete_el_iter != elementsToDelete.end(); ++delete_el_iter)
    {
        drawReg->UnregisterElement((**delete_el_iter).getRectangle());
        elements.erase(*delete_el_iter);
    }
        
    elementsToDelete.clear();
}

void HyperBlock::registerForDeletion(std::list<Block>::const_iterator block_iter)
{
    this->elementsToDelete.push_back(block_iter);
}

std::list<Block>* HyperBlock::getElements()
{
    std::list<Block>* list_p = &this->elements;
    return list_p;
}

Uint8 HyperBlock::getHighestCollidedRow() const 
{
    return this->highestCollidedRow;
}

void HyperBlock::setHighestCollidedRow(Uint8 rowNr)
{
    this->highestCollidedRow = rowNr;
}