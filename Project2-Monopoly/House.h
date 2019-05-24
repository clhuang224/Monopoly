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

    // 取得當下等級
    unsigned getLevel();

    // 設定等級 sign也會隨之改變
    void setLevel(unsigned newLevel);

    // 取得當下價格
    unsigned getPrice();

private:
    unsigned level;
    vector<unsigned> priceList;
    int owner;
};

#endif // !HOUSE_H

