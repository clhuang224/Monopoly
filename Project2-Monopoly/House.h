#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
class House :
    public Block
{
public:
    House(unsigned newPosition, string newName, int newType, unsigned newLevel, vector<unsigned> newPriceList);

    // 取得當下等級
    unsigned getLevel();

    // 設定等級 sign也會隨之改變
    void setLevel(unsigned newLevel);

    // 取得當下價格
    unsigned getPrice();

private:
    unsigned level;
    vector<unsigned> priceList;
};

#endif // !HOUSE_H

