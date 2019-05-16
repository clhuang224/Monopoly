#include "House.h"

House::House(unsigned newPosition, unsigned newType, unsigned newLevel) : Block(newPosition,newType)
{
    level = newLevel;
    // price = 依據文件的level跟type找出對應的價錢
}

unsigned House::getLevel()
{
    return level;
}

void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    // price = 依據文件的level跟type找出對應的價錢
}