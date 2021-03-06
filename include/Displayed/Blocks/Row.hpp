#pragma once

#include <list>

#include "Block.hpp"
#include "Rectangle.hpp"

class Row{
public:
    Row(Uint8 numberOfBlocks, Uint16 startPosX, Uint16 startPosY, Uint16 blockH,
        Uint8 blockSpacing, const Uint16& windowWidth,
        Uint8 red, Uint8 green, Uint8 blue);

    Uint16 calculateBlockWidth(Uint16 windowWidth, Uint8 numberOfBlocks,
                              Uint16 startPosX, Uint8 blockSpacingX);
    std::list<Block> elements;

private:
    Rectangle rowCollider;
};