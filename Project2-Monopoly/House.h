#pragma once
#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned, unsigned, unsigned);
    unsigned getLevel();
    void setLevel(unsigned);

private:
    unsigned level;
    unsigned price;
};

