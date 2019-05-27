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
		  unsigned cost=0,
          vector<unsigned> newPriceList = {0,0,0,0},
          vector<unsigned> newPasserby = {},
          int newOwner = -1);

    // 眔讽单
    unsigned getLevel();

	// 眔讽基
	unsigned getPrice();

	// 砞﹚单 sign穦繦ぇэ跑
    void setLevel(unsigned newLevel);

	//砞﹚局Τ
	void setOwner(int playerID);
private:
    unsigned level;
	//﹍基⊿逆  by辰甶
	unsigned cost_of_own;
    vector<unsigned> tollsList;
    int owner;
};

#endif // !HOUSE_H

