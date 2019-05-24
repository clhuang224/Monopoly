#include "Block.h"

Block::Block(unsigned newPosition, string newName, int newType, vector<string> newSign)
{
    position = newPosition;
    name = newName;
    type = newType;
    switch (type)
    {
    case 0:
        sign = { "         ",
                 "  ¢b¢b¢© ",
                 "  ¢v¢v¢« ",
                 "         " };
        break;
    default:
        sign = newSign;
    }
    
}

int Block::getType()
{
    return type;
}

string Block::getName()
{
    return name;
}

vector<string> Block::getSign()
{
    return sign;
}

 void Block::setSign(vector<string> newSign)
{
    sign = newSign;
}