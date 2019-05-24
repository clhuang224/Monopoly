#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned, string, unsigned, unsigned);

    // ���o��U����
    unsigned getLevel();

    // �]�w���� sign�]�|�H������
    void setLevel(unsigned);

    // ���o��U����
    unsigned getPrice();

private:
    unsigned level;
    vector<unsigned> priceList;
};

#endif // !HOUSE_H

