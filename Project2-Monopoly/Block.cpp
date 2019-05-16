#include "Block.h"

Block::Block(unsigned newPosition, unsigned newType)
{
    position = newPosition;
    type = newType;
}

unsigned Block::getType()
{
    return type;
}