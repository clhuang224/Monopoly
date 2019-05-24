#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned newPosition, string newName, int newType, unsigned newLevel, vector<unsigned> newPriceList);

    // ���o��U����
    unsigned getLevel();

    // �]�w���� sign�]�|�H������
    void setLevel(unsigned newLevel);

    // ���o��U����
    unsigned getPrice();

private:
    unsigned level;
    vector<unsigned> priceList;
};

#endif // !HOUSE_H

