#include "House.h"

House::House(unsigned newPosition, unsigned newType, unsigned newLevel) : Block(newPosition,newType)
{
    level = newLevel;
    // price = �̾ڤ��level��type��X����������
}

unsigned House::getLevel()
{
    return level;
}

void House::setLevel(unsigned newLevel)
{
    level = newLevel;
    // price = �̾ڤ��level��type��X����������
}