#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned newPosition,
          string newName,
          unsigned newLevel = 0,
          vector<unsigned> newPriceList = {0,0,0,0},
          vector<unsigned> newPasserby = {},
          int newOwner = -1);

    // ���o��U����
    unsigned getLevel();

    // �]�w���� sign�]�|�H������
    void setLevel(unsigned newLevel);

    // ���o��U����
    unsigned getPrice();

private:
    unsigned level;
    vector<unsigned> priceList;
    int owner;
};

#endif // !HOUSE_H

